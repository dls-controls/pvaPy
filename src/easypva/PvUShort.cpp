#include "PvUShort.h"
#include "PvType.h"
#include "PyUtility.h"

namespace epics { namespace pvaPy {


boost::python::dict PvUShort::createStructureDict()
{
    boost::python::dict pyDict;
    pyDict[ValueFieldKey] = PvType::UShort;
    return pyDict;
}

PvUShort::PvUShort()
    : PvScalar(createStructureDict())
{
    set(0);
}

PvUShort::PvUShort(epics::pvData::uint16 us)
    : PvScalar(createStructureDict())
{
    set(us);
}

PvUShort::~PvUShort()
{
}

void PvUShort::set(epics::pvData::uint16 us) 
{
    pvStructurePtr->getUShortField(ValueFieldKey)->put(us);
}

epics::pvData::uint16 PvUShort::get() const 
{
    return pvStructurePtr->getUShortField(ValueFieldKey)->get();
}

}}


