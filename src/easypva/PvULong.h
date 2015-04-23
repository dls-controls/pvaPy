#ifndef PV_ULONG_H
#define PV_ULONG_H

#include "pv/pvData.h"
#include "PvScalar.h"

namespace epics { namespace pvaPy {

class PvULong : public PvScalar
{
public:
    PvULong();
    PvULong(epics::pvData::uint64 ull);
    virtual ~PvULong();

    void set(epics::pvData::uint64 ull);
    epics::pvData::uint64 get() const;
private:
    static boost::python::dict createStructureDict();
};

}}
#endif
