// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution


#include "EndpointImpl.h"
#include "RpcServiceImpl.h"
#include "GetServiceImpl.h"
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


