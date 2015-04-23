#ifndef PV_INT_H
#define PV_INT_H

#include "pv/pvData.h"
#include "PvScalar.h"

namespace epics { namespace pvaPy {

class PvInt : public PvScalar
{
public:
    PvInt();
    PvInt(epics::pvData::int32 i);
    virtual ~PvInt();

    void set(epics::pvData::int32 i);
    epics::pvData::int32 get() const;
private:
    static boost::python::dict createStructureDict();
};

}}
#endif
