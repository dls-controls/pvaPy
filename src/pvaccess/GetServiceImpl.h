// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

#ifndef GET_SERVICE_IMPL_H
#define GET_SERVICE_IMPL_H

#include "pv/pvData.h"
#include "pv/pvAccess.h"
#include "pv/pvaServer.h"
#include "boost/python/object.hpp"


class GetServiceImpl : public epics::pvLocal::GetService
{
public:
    POINTER_DEFINITIONS(GetServiceImpl);
    GetServiceImpl(const boost::python::object& pyService);

    virtual void get();

    virtual epics::pvData::PVStructurePtr getPVStructure();

    virtual ~GetServiceImpl();

private:
    boost::python::object pyService;
};

#endif
