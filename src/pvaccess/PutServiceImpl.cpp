// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#include "boost/python/extract.hpp"
#include "boost/python/call_method.hpp"
#include "PutServiceImpl.h"
#include "PvObject.h"
#include "PyGilManager.h"

PutServiceImpl::PutServiceImpl(const boost::python::object& pyService_) : 
    pyService(pyService_)
{
}

void PutServiceImpl::put(epics::pvData::PVStructurePtr const &pvStructure,
        epics::pvData::BitSetPtr const &bitSet)
{
    using namespace boost::python;

    PvObject pyStructure(pvStructure);

    PyGilManager::gilStateEnsure();
 
    call_method<void, PvObject>(pyService.ptr(), "put", pyStructure);

    PyGilManager::gilStateRelease();
}


void PutServiceImpl::get()
{
    using namespace boost::python;
    PyGilManager::gilStateEnsure();

    call_method<void>(pyService.ptr(), "get");

    PyGilManager::gilStateRelease();
}

epics::pvData::PVStructurePtr PutServiceImpl::getPVStructure()
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

PutServiceImpl::~PutServiceImpl()
{
    PyGilManager::gilStateEnsure();
    boost::python::object dummy;
    pyService = dummy;
    PyGilManager::gilStateRelease();
}



