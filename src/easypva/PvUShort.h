#ifndef PV_USHORT_H
#define PV_USHORT_H

#include "pv/pvData.h"
#include "PvScalar.h"

namespace epics { namespace pvaPy {

class PvUShort : public PvScalar
{
public:
    PvUShort();
    PvUShort(epics::pvData::uint16 us);
    virtual ~PvUShort();

    void set(epics::pvData::uint16 us);
    epics::pvData::uint16 get() const;
private:
    static boost::python::dict createStructureDict();
};

}}
#endif
