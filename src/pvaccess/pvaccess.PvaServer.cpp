// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#include "boost/python/class.hpp"
#include "boost/python/overloads.hpp"
#include "PvaServer.h"


using namespace boost::python;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(PvaServerListen, PvaServer::listen, 0, 1)

//
// PVA Server class
//
void wrapPvaServer() 
{

class_<PvaServer>("PvaServer", 
    "PvaServer is class used for hosting PVA. One instance of PvaServer can host multiple endpoints.\n\n"
    "**PvaServer()**:\n\n"
    "\t::\n\n"
    "\t\tpvaServer = PvaServer()\n\n", 
    init<>())

    .def("registerService", 
        &PvaServer::registerService, 
        args("serviceName", "serviceImpl"), 
        "Registers service implementation with RPC server. Typically, all services are registered before RPC server starts listening for client requests.\n\n"
        ":Parameter: *serviceName* (str) - service name (name of the PV channel used for RPC client/server communication)\n\n"
        ":Parameter: *serviceImpl* (object) - reference to service implementation object (e.g., python function) that returns PV Object upon invocation\n\n"
        "The following is an example of RPC service that creates NT Table according to client specifications:\n\n"
        "::\n\n"
        "    import pvaccess\n\n"
        "    import random\n\n"
        "    def createNtTable(pvRequest):\n\n"
        "        nRows = x.getInt('nRows')\n\n"
        "        nColumns = x.getInt('nColumns')\n\n"
        "        print 'Creating table with %d rows and %d columns' % (nRows, nColumns)\n\n"
        "        ntTable = pvaccess.NtTable(nColumns, pvaccess.DOUBLE)\n\n"
        "        labels = []\n\n"
        "        for j in range (0, nColumns):\n\n"
        "            labels.append('Column%s' % j)\n\n"
        "            column = []\n\n"
        "            for i in range (0, nRows):\n\n"
        "                column.append(random.uniform(0,1))\n\n"
        "            ntTable.setColumn(j, column)\n\n"
        "        ntTable.setLabels(labels)\n\n"
        "        ntTable.setDescriptor('Automatically created by pvaPy RPC Server')\n\n"
        "        return ntTable\n\n"
        "    \n\n"
        "    pvaServer = pvaccess.PvaServer()\n\n"
        "    pvaServer.registerService('createNtTable', createNtTable)\n\n"
        "    pvaServer.listen()\n\n")

    .def("unregisterService", 
        &PvaServer::unregisterService, 
        args("serviceName"), 
        "Unregisters given service from RPC server.\n\n"
        ":Parameter: *serviceName* (str) - service name (name of the PV channel used for RPC client/server communication)\n\n"
        "::\n\n"
        "    pvaServer.unregisterService('createNtTable')\n\n")

    .def("registerEndpoint", 
        &PvaServer::registerEndpoint, 
        args("endpointName", "endpointImpl"), 
        "")

    .def("startListener", 
        &PvaServer::startListener, 
        "Starts PVA listener in its own thread. This method is typically used for multi-threaded programs, or for testing and debugging in python interactive mode. It should be used in conjunction with *stopListener()* call.\n\n"
        "::\n\n"
        "    pvaServer.startListener()\n\n")

    .def("stopListener", 
        &PvaServer::stopListener, 
        "Stops PVA listener thread. This method is used in conjunction with *startListener()* call.\n\n"
        "::\n\n"
        "    pvaServer.stopListener()\n\n")

    .def("start", 
        &PvaServer::start, 
        "Start serving PVA requests. This method is equivalent to *listen()*, and blocks until either *stop()* or *shutdown()* methods are invoked.\n\n"
        "::\n\n"
        "    pvaServer.start()\n\n")

    .def("stop", 
        &PvaServer::stop, 
        "Stop serving PVA requests. This method is equivalent to *shutdown()*.\n\n"
        "::\n\n"
        "    pvaServer.stop()\n\n")

    .def("listen", 
        static_cast<void(PvaServer::*)(int)>(&PvaServer::listen), 
        PvaServerListen(args("seconds=0"), 
        "Start serving PVA requests.\n\n"
        ":Parameter: *seconds* (int) - specifies the amount of time server should be listening for requests (0 indicates 'forever')\n\n"
        "::\n\n"
        "    pvaServer.listen(60)\n\n"))

    .def("shutdown", 
        &PvaServer::shutdown, 
        "Stop serving PVA requests. This method is equivalent to *stop()*.\n\n"
        "::\n\n"
        "    pvaServer.shutdown()\n\n")
;

} // wrapPvaServer()

