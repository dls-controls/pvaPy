#include "PvUByte.h"
#include "PvType.h"
#include "PyUtility.h"

namespace epics { namespace pvaPy {


boost::python::dict PvUByte::createStructureDict()
{
    boost::python::dict pyDict;
    pyDict[ValueFieldKey] = PvType::UByte;
    return pyDict;
}

PvUByte::PvUByte()
    : PvScalar(createStructureDict())
{
    set(0);
}

PvUByte::PvUByte(epics::pvData::uint8 uc)
    : PvScalar(createStructureDict())
{
    set(uc);
}

PvUByte::~PvUByte()
{
}

void PvUByte::set(epics::pvData::uint8 uc) 
{
    pvStructurePtr->getUByteField(ValueFieldKey)->put(uc);
}

epics::pvData::uint8 PvUByte::get() const 
{
    return pvStructurePtr->getUByteField(ValueFieldKey)->get();
}

}}


