// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#ifndef PVA_SERVERIMPL_H
#define PVA_SERVERIMPL_H

#include <string>

#include "pv/pvData.h"
#include "pv/pvAccess.h"

#include "pv/pvaServer.h"

#include "boost/python/object.hpp"
#include "RpcServiceImpl.h"
#include "PvaPyLogger.h"

class PvaServer : public epics::pvLocal::PVAServer
{
public:
    PvaServer();
    virtual ~PvaServer();
    void registerService(const std::string& serviceName, const boost::python::object& pyService);

    void unregisterService(const std::string& serviceName);

    void registerEndpoint(const std::string& serviceName, const boost::python::object& pyEndpoint);

    void startListener();
    void stopListener();

    void listen(int seconds=0);
    void start();
    void stop();
    void shutdown();
private:
    static const double ShutdownWaitTime;
    static PvaPyLogger logger;
    static void listenerThread(PvaServer* rpcServer);
    bool destroyed;
};

#endif
