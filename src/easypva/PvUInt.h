#ifndef PV_UINT_H
#define PV_UINT_H

#include "pv/pvData.h"
#include "PvScalar.h"

namespace epics { namespace pvaPy {

class PvUInt : public PvScalar
{
public:
    PvUInt();
    PvUInt(epics::pvData::uint32 ui);
    virtual ~PvUInt();

    void set(epics::pvData::uint32 ui);
    epics::pvData::uint32 get() const;
private:
    static boost::python::dict createStructureDict();
};

}}
#endif
