// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#ifndef ENDPOINTIMPL_H
#define ENDPOINTIMPL_H

#include <stdexcept>
#include "boost/python/object.hpp"
#include "boost/python/extract.hpp"

#include <pv/sharedPtr.h>
#include <pv/pvAccess.h>
#include <pv/endpoint.h>

#include <shareLib.h>


class epicsShareClass EndpointGetImpl : public epics::pvLocal::EndpointGet
{
public:
    EndpointGetImpl(const boost::python::object& pyGet)
    : m_pyGet(pyGet)
    {}

    virtual epics::pvLocal::GetService::shared_pointer getGetService(epics::pvData::PVStructure::shared_pointer const & pvRequest);

    virtual ~EndpointGetImpl() {};

private:
    boost::python::object m_pyGet;
};


class epicsShareClass EndpointRPCImpl : public  epics::pvLocal::EndpointRPC
{
public:
    EndpointRPCImpl(const boost::python::object& pyRPC)
    : m_pyRPC(pyRPC)
    {}

    virtual epics::pvLocal::Service::shared_pointer getRpcService(epics::pvData::PVStructure::shared_pointer const &);

    virtual ~EndpointRPCImpl() {};

private:
    boost::python::object m_pyRPC;
};

class epicsShareClass EndpointMonitorImpl : public  epics::pvLocal::EndpointMonitor
{
public:
    EndpointMonitorImpl(const boost::python::object& pyMon)
    : m_pyMon(pyMon)
    {}

    virtual epics::pvLocal::MonitorService::shared_pointer getMonitorService(epics::pvData::PVStructure::shared_pointer const &);

    virtual ~EndpointMonitorImpl() {};

private:
    boost::python::object m_pyMon;
};

class epicsShareClass EndpointImpl
 : public epics::pvLocal::Endpoint,
   public std::tr1::enable_shared_from_this<EndpointImpl>
{
public:
    POINTER_DEFINITIONS(EndpointImpl);
    EndpointImpl(const boost::python::object& pyEndpoint)
    : m_pyEndpoint(pyEndpoint)
    {}

    virtual epics::pvLocal::EndpointGetPtr getEndpointGet();

    virtual epics::pvLocal::EndpointRPCPtr getEndpointRPC();

    virtual epics::pvLocal::EndpointMonitorPtr getEndpointMonitor();

private:
    boost::python::object m_pyEndpoint;
};

#endif  /* ENDPOINTIMPL_H */
