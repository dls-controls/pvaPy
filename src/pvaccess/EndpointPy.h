// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#ifndef EndpointPy_H
#define EndpointPy_H
#include <stdexcept>
#include "boost/python/object.hpp"
#include "boost/python/extract.hpp"

#include <pv/sharedPtr.h>

#include <pv/pvAccess.h>

#include <pv/endpoint.h>

#include <shareLib.h>


class epicsShareClass EndpointPy
{
public:
    POINTER_DEFINITIONS(EndpointPy);
    EndpointPy() {}

    void registerEndpointRPC(const boost::python::object & pyService);

    void registerService(const boost::python::object& pyService);

    void registerEndpointGet(const boost::python::object & pyGet);

    void registerEndpointPut(const boost::python::object & pyPut);

    void registerEndpointMonitor(const boost::python::object & pyMon);

    boost::python::object m_pyRPC;
    boost::python::object m_pyService;
    boost::python::object m_pyGet;
    boost::python::object m_pyPut;
    boost::python::object m_pyMon;
};


typedef std::tr1::shared_ptr<EndpointPy> EndpointPyPtr;


#endif  /* EndpointPy_H */
