#ifndef PV_TIME_STAMP_H
#define PV_TIME_STAMP_H

#include "boost/python/dict.hpp"
#include "PvObject.h"

namespace epics { namespace pvaPy {


class PvTimeStamp : public PvObject
{
public:
    // Constants
    static const char* StructureId;

    static const char* SecondsPastEpochFieldKey;
    static const char* NanosecondsFieldKey;
    static const char* UserTagFieldKey;

    static const epics::pvData::int32 UnknownUserTag;

    // Static methods
    static boost::python::dict createStructureDict();

    // Instance methods
    PvTimeStamp();
    PvTimeStamp(epics::pvData::int64  secondsPastEpoch, epics::pvData::int32 nanoseconds);
    PvTimeStamp(epics::pvData::int64  secondsPastEpoch, epics::pvData::int32 nanoseconds, epics::pvData::int32 userTag);
    PvTimeStamp(const boost::python::dict& pyDict, const std::string& structureId=StructureId);
    PvTimeStamp(const epics::pvData::PVStructurePtr& pvStructurePtr);
    PvTimeStamp(const PvTimeStamp& pvTimeStamp); 
    virtual ~PvTimeStamp();

    virtual void setSecondsPastEpoch(epics::pvData::int64  secondsPastEpoch);
    virtual epics::pvData::int64  getSecondsPastEpoch() const;
    virtual void setNanoseconds(epics::pvData::int32 nanoseconds);
    virtual epics::pvData::int32 getNanoseconds() const;
    virtual void setUserTag(epics::pvData::int32 userTag);
    virtual epics::pvData::int32 getUserTag() const;

};


}}
#endif
