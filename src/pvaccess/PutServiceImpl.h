// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#ifndef PUT_SERVICE_IMPL_H
#define PUT_SERVICE_IMPL_H

#include "pv/pvData.h"
#include "pv/pvAccess.h"
#include "pv/pvaServer.h"
#include "boost/python/object.hpp"


class PutServiceImpl : public epics::pvLocal::PutService
{
public:
    POINTER_DEFINITIONS(PutServiceImpl);
    PutServiceImpl(const boost::python::object& pyService);

    virtual void put(epics::pvData::PVStructurePtr const &pvStructure,
        epics::pvData::BitSetPtr const &bitSet);

    virtual void get();

    virtual epics::pvData::PVStructurePtr getPVStructure();

    virtual ~PutServiceImpl();

private:
    boost::python::object pyService;
};

#endif
