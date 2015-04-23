#ifndef PV_BYTE_H
#define PV_BYTE_H

#include "pv/pvData.h"
#include "PvScalar.h"

namespace epics { namespace pvaPy {

class PvByte : public PvScalar
{
public:
    PvByte();
    PvByte(epics::pvData::int8 i);
    virtual ~PvByte();

    void set(epics::pvData::int8 i);
    epics::pvData::int8 get() const;
private:
    static boost::python::dict createStructureDict();
};

}}
#endif
