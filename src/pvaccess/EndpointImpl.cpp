// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution


#include "EndpointImpl.h"
#include "RpcServiceImpl.h"
#include "GetServiceImpl.h"
#include "PutServiceImpl.h"
#include "MonitorServiceImpl.h"
#include "EndpointPy.h"
#include "PvObject.h"
#include "PyGilManager.h"

using namespace epics::pvLocal;



epics::pvLocal::GetService::shared_pointer EndpointGetImpl::getGetService(epics::pvData::PVStructure::shared_pointer const & pvRequest)
{
    if (m_pyGet)
    {
        PvObject pyRequest(pvRequest);

        PyGilManager::gilStateEnsure();

        boost::python::object pyObject = m_pyGet(pyRequest);

        if (pyObject){
            epics::pvLocal::GetService::shared_pointer ptr = epics::pvLocal::GetService::shared_pointer(new GetServiceImpl(pyObject));
            PyGilManager::gilStateRelease();
            return ptr;
        }
        PyGilManager::gilStateRelease();
    }

    return GetService::shared_pointer();
}

epics::pvLocal::PutService::shared_pointer EndpointPutImpl::getPutService(epics::pvData::PVStructure::shared_pointer const & pvRequest)
{
    if (m_pyPut)
    {
        PvObject pyRequest(pvRequest);

        PyGilManager::gilStateEnsure();

        boost::python::object pyObject = m_pyPut(pyRequest);

        if (pyObject){
            epics::pvLocal::PutService::shared_pointer ptr = epics::pvLocal::PutService::shared_pointer(new PutServiceImpl(pyObject));
            PyGilManager::gilStateRelease();
            return ptr;
        }
        PyGilManager::gilStateRelease();
    }

    return PutService::shared_pointer();
}



epics::pvLocal::Service::shared_pointer EndpointRPCImpl::getRpcService(epics::pvData::PVStructure::shared_pointer const & pvRequest)
{
    if (m_pyRPC)
    {
        PvObject pyRequest(pvRequest);

        PyGilManager::gilStateEnsure();
    
        boost::python::object pyObject = m_pyRPC(pyRequest);

        PyGilManager::gilStateRelease();

        if (pyObject)
           return epics::pvLocal::Service::shared_pointer(new RpcServiceImpl(
                pyObject));
    }

    return epics::pvLocal::Service::shared_pointer();
}

epics::pvLocal::MonitorService::shared_pointer EndpointMonitorImpl::getMonitorService(epics::pvData::PVStructure::shared_pointer const & pvRequest)
{
    if (m_pyMon)
    {
        PvObject pyRequest(pvRequest);

        PyGilManager::gilStateEnsure();

        boost::python::object pyObject = m_pyMon(pyRequest);

        PyGilManager::gilStateRelease();

        if (pyObject)
        {
           MonitorServiceImplPtr xx = MonitorServiceImplPtr(new MonitorServiceImpl(pyObject));
           xx->init();
           return xx;
        }   
    }

    return epics::pvLocal::MonitorService::shared_pointer();
}


epics::pvLocal::EndpointGetPtr EndpointImpl::getEndpointGet()
{
    boost::python::extract<EndpointPy> pythonEndpointExtract(m_pyEndpoint);
    if (pythonEndpointExtract.check())
    {
        EndpointPy ep = pythonEndpointExtract();

        if (ep.m_pyGet)
        {
            return EndpointGetPtr(new EndpointGetImpl(ep.m_pyGet));
        }
    }
    return EndpointGetPtr();
}


epics::pvLocal::EndpointPutPtr EndpointImpl::getEndpointPut()
{
    boost::python::extract<EndpointPy> pythonEndpointExtract(m_pyEndpoint);
    if (pythonEndpointExtract.check())
    {
        EndpointPy ep = pythonEndpointExtract();

        if (ep.m_pyPut)
        {
            return EndpointPutPtr(new EndpointPutImpl(ep.m_pyPut));
        }
    }
    return EndpointPutPtr();
}


epics::pvLocal::EndpointRPCPtr EndpointImpl::getEndpointRPC()
{
    boost::python::extract<EndpointPy> pythonEndpointExtract(m_pyEndpoint);
    if (pythonEndpointExtract.check())
    {
        EndpointPy ep = pythonEndpointExtract();

        if (ep.m_pyRPC)
        {
            return EndpointRPCPtr(new EndpointRPCImpl(ep.m_pyRPC));
        }
    }
    return EndpointRPCPtr();
}

epics::pvLocal::EndpointMonitorPtr EndpointImpl::getEndpointMonitor()
{
    boost::python::extract<EndpointPy> pythonEndpointExtract(m_pyEndpoint);
    if (pythonEndpointExtract.check())
    {
        EndpointPy ep = pythonEndpointExtract();

        if (ep.m_pyMon)
        {
            return EndpointMonitorPtr(new EndpointMonitorImpl(ep.m_pyMon));
        }
    }
	return EndpointMonitorPtr();
}

