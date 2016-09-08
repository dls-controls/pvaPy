// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#include "boost/python/class.hpp"
#include "boost/python/overloads.hpp"
#include "PvaServer.h"
#include "EndpointPy.h"

using namespace boost::python;


void wrapEndpoint() 
{

class_<EndpointPy>("Endpoint", 
    "", 
    init<>())
    .def("registerService", 
        &EndpointPy::registerService, 
        args("service"), 
        "")
    .def("registerEndpointGet", 
        &EndpointPy::registerEndpointGet, 
        args("endpointGet"), 
        "")
    .def("registerEndpointPut", 
        &EndpointPy::registerEndpointPut, 
        args("endpointPut"), 
        "")
    .def("registerEndpointRPC", 
        &EndpointPy::registerEndpointRPC, 
        args("endpointRPC"), 
        "")

;

} // Endpoint()

