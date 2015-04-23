#ifndef PV_LONG_H
#define PV_LONG_H

#include "pv/pvData.h"
#include "PvScalar.h"

namespace epics { namespace pvaPy {

class PvLong : public PvScalar
{
public:
    PvLong();
    PvLong(epics::pvData::int64 ll);
    virtual ~PvLong();

    void set(epics::pvData::int64 ll);
    epics::pvData::int64 get() const;
private:
    static boost::python::dict createStructureDict();
};

}}
#endif
