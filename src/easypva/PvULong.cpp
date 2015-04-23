#include "PvULong.h"
#include "PvType.h"
#include "PyUtility.h"

namespace epics { namespace pvaPy {


boost::python::dict PvULong::createStructureDict()
{
    boost::python::dict pyDict;
    pyDict[ValueFieldKey] = PvType::ULong;
    return pyDict;
}

PvULong::PvULong()
    : PvScalar(createStructureDict())
{
    set(0);
}

PvULong::PvULong(epics::pvData::uint64 ull)
    : PvScalar(createStructureDict())
{
    set(ull);
}

PvULong::~PvULong()
{
}

void PvULong::set(epics::pvData::uint64 ull) 
{
    pvStructurePtr->getULongField(ValueFieldKey)->put(ull);
}

epics::pvData::uint64 PvULong::get() const 
{
    return pvStructurePtr->getULongField(ValueFieldKey)->get();
}

}}


