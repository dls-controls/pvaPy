// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#include "PvaServer.h"
#include "PyGilManager.h"
#include "InvalidState.h"
#include <pv/endpoint.h>
#include "EndpointPy.h"
#include "EndpointImpl.h"

PvaPyLogger PvaServer::logger("PvaServer");
const double PvaServer::ShutdownWaitTime(0.1);

PvaServer::PvaServer() :
    epics::pvLocal::PVAServer(),
    destroyed(false)
{
}

PvaServer::~PvaServer() 
{
    shutdown();
    epicsThreadSleep(ShutdownWaitTime);
}

void PvaServer::registerService(const std::string& serviceName, const boost::python::object& pyService)
{
    epics::pvLocal::RPCService::shared_pointer rpcServiceImplPtr(new RpcServiceImpl(pyService));
    epics::pvLocal::PVAServer::registerService(serviceName, rpcServiceImplPtr);
}

void PvaServer::unregisterService(const std::string& serviceName)
{
    epics::pvLocal::PVAServer::unregisterService(serviceName);
}


void PvaServer::registerEndpoint(const std::string& endpointName, const boost::python::object& pyEndpoint)
{
    epics::pvLocal::EndpointPtr endpoint(new EndpointImpl(pyEndpoint));
    epics::pvLocal::PVAServer::registerEndpoint(endpointName, endpoint);
}


void PvaServer::startListener()
{
    if (destroyed) {
        throw InvalidState("Invalid state: server has been shutdown and cannot be restarted.");
    }

    // One must call PyEval_InitThreads() in the main thread
    // to initialize thread state, which is needed for proper functioning
    // of PyGILState_Ensure()/PyGILState_Release().
    PyGilManager::evalInitThreads();
    epicsThreadCreate("PvaServerListenerThread", epicsThreadPriorityLow, epicsThreadGetStackSize(epicsThreadStackSmall), (EPICSTHREADFUNC)listenerThread, this);
}

void PvaServer::stopListener()
{
    shutdown();
}

void PvaServer::listenerThread(PvaServer* server)
{
    logger.debug("Started listener thread %s", epicsThreadGetNameSelf());

    // Handle possible exceptions 
    try {
        server->run();
    }
    catch (const std::exception& ex) {
    // Not good.
        logger.error("Exception caught in listener thread %s: %s", epicsThreadGetNameSelf(), ex.what());
    }
}

void PvaServer::listen(int seconds)
{
    if (destroyed) {
        throw InvalidState("Invalid state: server has been shutdown and cannot be restarted.");
    }
    printInfo();
    run(seconds);
    destroyed = true;
}

void PvaServer::start()
{
    listen();
}

void PvaServer::stop()
{
    shutdown();
}

void PvaServer::shutdown()
{
    destroyed = true;
    epics::pvLocal::PVAServer::destroy();
}

