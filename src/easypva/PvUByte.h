#ifndef PV_UBYTE_H
#define PV_UBYTE_H

#include "pv/pvData.h"
#include "PvScalar.h"

namespace epics { namespace pvaPy {

class PvUByte : public PvScalar
{
public:
    PvUByte();
    PvUByte(epics::pvData::uint8 uc);
    virtual ~PvUByte();

    void set(epics::pvData::uint8 uc);
    epics::pvData::uint8 get() const;
private:
    static boost::python::dict createStructureDict();
};

}}
#endif
