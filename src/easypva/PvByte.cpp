#include "PvByte.h"
#include "PvType.h"
#include "PyUtility.h"

namespace epics { namespace pvaPy {

using namespace epics::pvData;


boost::python::dict PvByte::createStructureDict()
{
    boost::python::dict pyDict;
    pyDict[ValueFieldKey] = PvType::Byte;
    return pyDict;
}

PvByte::PvByte()
    : PvScalar(createStructureDict())
{
    set(0);
}

PvByte::PvByte(int8 c)
    : PvScalar(createStructureDict())
{
    set(c);
}

PvByte::~PvByte()
{
}

void PvByte::set(int8 c) 
{
    pvStructurePtr->getByteField(ValueFieldKey)->put(c);
}

int8 PvByte::get() const 
{
    return pvStructurePtr->getByteField(ValueFieldKey)->get();
}



}}
