#ifndef PV_SHORT_H
#define PV_SHORT_H

#include "pv/pvData.h"
#include "PvScalar.h"

namespace epics { namespace pvaPy {

class PvShort : public PvScalar
{
public:
    PvShort();
    PvShort(epics::pvData::int16 s);
    virtual ~PvShort();

    void set(epics::pvData::int16 s);
    epics::pvData::int16 get() const;
private:
    static boost::python::dict createStructureDict();
};

}}
#endif
