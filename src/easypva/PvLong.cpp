#include "PvLong.h"
#include "PvType.h"
#include "PyUtility.h"

namespace epics { namespace pvaPy {


boost::python::dict PvLong::createStructureDict()
{
    boost::python::dict pyDict;
    pyDict[ValueFieldKey] = PvType::Long;
    return pyDict;
}

PvLong::PvLong()
    : PvScalar(createStructureDict())
{
    set(0);
}

PvLong::PvLong(epics::pvData::int64 ll)
    : PvScalar(createStructureDict())
{
    set(ll);
}

PvLong::~PvLong()
{
}

void PvLong::set(epics::pvData::int64 ll) 
{
    pvStructurePtr->getLongField(ValueFieldKey)->put(ll);
}

epics::pvData::int64 PvLong::get() const 
{
    return pvStructurePtr->getLongField(ValueFieldKey)->get();
}

}}


