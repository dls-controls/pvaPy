// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#include "boost/python/extract.hpp"
#include "boost/python/call_method.hpp"
#include "GetServiceImpl.h"
#include "PvObject.h"
#include "PyGilManager.h"

GetServiceImpl::GetServiceImpl(const boost::python::object& pyService_) : 
    pyService(pyService_)
{
}

void GetServiceImpl::get()
{
    using namespace boost::python;
    PyGilManager::gilStateEnsure();
    call_method<void>(pyService.ptr(), "get");

    PyGilManager::gilStateRelease();

}

epics::pvData::PVStructurePtr GetServiceImpl::getPVStructure()
{
    using namespace epics::pvData;
    using namespace boost::python;

    // Acquire GIL
    PyGilManager::gilStateEnsure();

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

GetServiceImpl::~GetServiceImpl()
{
}



