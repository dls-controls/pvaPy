/*
 * MonitorServiceImpl.cpp
 *
 *  Created on: 31 Aug 2016
 *      Author: gnx91527
 */

#include "MonitorServiceImpl.h"
#include "boost/python/extract.hpp"
#include "boost/python/call_method.hpp"
#include "PvObject.h"
#include "PyGilManager.h"

MonitorServiceImpl::MonitorServiceImpl(const boost::python::object& pyService):
    pyService(pyService)
{
}

void MonitorServiceImpl::init()
{
    PyGilManager::gilStateEnsure();

    // Call into python object to request the structure
    boost::python::object pyObject = boost::python::call_method<boost::python::object>(pyService.ptr(), "getUpdater");

    boost::python::extract<MonitorServiceUpdater &> updaterExtract(pyObject);
    if (updaterExtract.check()) {
        MonitorServiceUpdater & updater = updaterExtract();
        updater.registerMonitorService(shared_from_this());
    }

    // Release GIL.
    PyGilManager::gilStateRelease();
}

MonitorServiceImpl::~MonitorServiceImpl()
{
    PyGilManager::gilStateEnsure();
    boost::python::object dummy;
    pyService = dummy;
    PyGilManager::gilStateRelease();
}

void MonitorServiceImpl::addListener(epics::pvLocal::MonitorServiceListenerPtr const & listener)
{
    this->listener = listener;
}


epics::pvData::PVStructurePtr MonitorServiceImpl::getPVStructure()
{
    using namespace epics::pvData;
    using namespace boost::python;

    // Acquire GIL
    PyGilManager::gilStateEnsure();

    // Call into python object to request the structure
    object pyObject = call_method<object>(pyService.ptr(), "getPVStructure");

    // Release GIL.
    PyGilManager::gilStateRelease();

    boost::python::extract<PvObject> pvObjectExtract(pyObject);
    if (!pvObjectExtract.check()) {
        epics::pvData::StructureConstPtr s = epics::pvData::getFieldCreate()->
            createFieldBuilder()->createStructure();
        return getPVDataCreate()->createPVStructure(s);
    }
    PvObject pyResponse = pvObjectExtract();
    return static_cast<epics::pvData::PVStructurePtr>(pyResponse);
}

