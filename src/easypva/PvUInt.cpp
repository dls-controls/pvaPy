#include "PvUInt.h"
#include "PvType.h"
#include "PyUtility.h"

namespace epics { namespace pvaPy {


boost::python::dict PvUInt::createStructureDict()
{
    boost::python::dict pyDict;
    pyDict[ValueFieldKey] = PvType::UInt;
    return pyDict;
}

PvUInt::PvUInt()
    : PvScalar(createStructureDict())
{
    set(0);
}

PvUInt::PvUInt(epics::pvData::uint32 ui)
    : PvScalar(createStructureDict())
{
    set(ui);
}

PvUInt::~PvUInt()
{
}

void PvUInt::set(epics::pvData::uint32 ui) 
{
    pvStructurePtr->getUIntField(ValueFieldKey)->put(ui);
}

epics::pvData::uint32 PvUInt::get() const 
{
    return pvStructurePtr->getUIntField(ValueFieldKey)->get();
}

}}


