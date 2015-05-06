
#include "Union.h"


using namespace epics::pvData;
using namespace boost::python;
using namespace std;

namespace epics { namespace pvaPy {

Union::Union()
{
    union_p = getFieldCreate()->createVariantUnion();
}

Union::Union(const PvObject& pvObject)
{
    PVStructurePtr pvStructure = pvObject.getPvStructurePtr();
    StructureConstPtr structure = pvStructure->getStructure();
    union_p = getFieldCreate()->createUnion(
        structure->getFieldNames(),
        structure->getFields());
}

std::ostream& operator<<(std::ostream& out, const Union& u)
{
    out << u.getUnion() << endl;
    return out;
}

}}

