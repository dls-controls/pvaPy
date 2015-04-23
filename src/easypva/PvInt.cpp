#include "PvInt.h"
#include "PvType.h"
#include "PyUtility.h"

namespace epics { namespace pvaPy {


boost::python::dict PvInt::createStructureDict()
{
    boost::python::dict pyDict;
    pyDict[ValueFieldKey] = PvType::Int;
    return pyDict;
}

PvInt::PvInt()
    : PvScalar(createStructureDict())
{
    set(0);
}

PvInt::PvInt(epics::pvData::int32 i)
    : PvScalar(createStructureDict())
{
    set(i);
}

PvInt::~PvInt()
{
}

void PvInt::set(epics::pvData::int32 i) 
{
    pvStructurePtr->getIntField(ValueFieldKey)->put(i);
}

epics::pvData::int32 PvInt::get() const 
{
    return pvStructurePtr->getIntField(ValueFieldKey)->get();
}

}}


