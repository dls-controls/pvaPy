// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#include "boost/python/class.hpp"
#include "boost/python/overloads.hpp"
#include "MonitorServiceImpl.h"


using namespace boost::python;

//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(PvaServerListen, PvaServer::listen, 0, 1)

//
// PVA Server class
//
void wrapMonitorServiceUpdater() 
{

class_<MonitorServiceUpdater>("MonitorServiceUpdater", 
    "TODO",
    init<>())
    .def("update", 
        &MonitorServiceUpdater::update, 
        "TODO")
;

} // wrapPvaServer()

