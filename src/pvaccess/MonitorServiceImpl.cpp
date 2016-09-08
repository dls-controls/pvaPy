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

MonitorServiceImpl::~MonitorServiceImpl()
{
	// TODO Auto-generated destructor stub
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

