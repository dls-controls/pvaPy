#include "PvShort.h"
#include "PvType.h"
#include "PyUtility.h"

namespace epics { namespace pvaPy {


boost::python::dict PvShort::createStructureDict()
{
    boost::python::dict pyDict;
    pyDict[ValueFieldKey] = PvType::Short;
    return pyDict;
}

PvShort::PvShort()
    : PvScalar(createStructureDict())
{
    set(0);
}

PvShort::PvShort(epics::pvData::int16 s)
    : PvScalar(createStructureDict())
{
    set(s);
}

PvShort::~PvShort()
{
}

void PvShort::set(epics::pvData::int16 s) 
{
    pvStructurePtr->getShortField(ValueFieldKey)->put(s);
}

epics::pvData::int16 PvShort::get() const 
{
    return pvStructurePtr->getShortField(ValueFieldKey)->get();
}

}}


