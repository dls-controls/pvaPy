#include "PvTimeStamp.h"
#include "PvType.h"

namespace epics { namespace pvaPy {


const char* PvTimeStamp::StructureId("time_t");

const char* PvTimeStamp::SecondsPastEpochFieldKey("secondsPastEpoch");
const char* PvTimeStamp::NanosecondsFieldKey("nanoseconds");
const char* PvTimeStamp::UserTagFieldKey("userTag");

const epics::pvData::int32 PvTimeStamp::UnknownUserTag(-1);

boost::python::dict PvTimeStamp::createStructureDict()
{
    // StandardField implementation is using signed types for some reason.
    boost::python::dict pyDict;
    pyDict[SecondsPastEpochFieldKey] = PvType::Long;
    pyDict[NanosecondsFieldKey] = PvType::Int;
    pyDict[UserTagFieldKey] = PvType::Int;
    return pyDict;
}

PvTimeStamp::PvTimeStamp()
    : PvObject(createStructureDict(), StructureId)
{
    setSecondsPastEpoch(0);
    setNanoseconds(0);
    setUserTag(UnknownUserTag);
}

PvTimeStamp::PvTimeStamp(epics::pvData::int64 secondsPastEpoch, epics::pvData::int32 nanoseconds)
    : PvObject(createStructureDict(), StructureId)
{
    setSecondsPastEpoch(secondsPastEpoch);
    setNanoseconds(nanoseconds);
    setUserTag(UnknownUserTag);
}

PvTimeStamp::PvTimeStamp(epics::pvData::int64 secondsPastEpoch, epics::pvData::int32 nanoseconds, epics::pvData::int32 userTag)
    : PvObject(createStructureDict(), StructureId)
{
    setSecondsPastEpoch(secondsPastEpoch);
    setNanoseconds(nanoseconds);
    setUserTag(userTag);
}

PvTimeStamp::PvTimeStamp(const boost::python::dict& pyDict, const std::string& structureId)
    : PvObject(pyDict, structureId)
{
}

PvTimeStamp::PvTimeStamp(const PvTimeStamp& pvTimeStamp)
    : PvObject(pvTimeStamp.pvStructurePtr)
{
}

PvTimeStamp::PvTimeStamp(const epics::pvData::PVStructurePtr& pvStructurePtr)
    : PvObject(pvStructurePtr)
{
}

PvTimeStamp::~PvTimeStamp()
{
}

void PvTimeStamp::setSecondsPastEpoch(epics::pvData::int64 long secondsPastEpoch)
{
    pvStructurePtr->getLongField(SecondsPastEpochFieldKey)->put(secondsPastEpoch);
}

epics::pvData::int64 long PvTimeStamp::getSecondsPastEpoch() const
{
    return pvStructurePtr->getLongField(SecondsPastEpochFieldKey)->get();
}

void PvTimeStamp::setNanoseconds(epics::pvData::int32 nanoseconds)
{
    pvStructurePtr->getIntField(NanosecondsFieldKey)->put(nanoseconds);
}

epics::pvData::int32 PvTimeStamp::getNanoseconds() const
{
    return pvStructurePtr->getIntField(NanosecondsFieldKey)->get();
}

void PvTimeStamp::setUserTag(epics::pvData::int32 userTag)
{
    pvStructurePtr->getIntField(UserTagFieldKey)->put(userTag);
}

epics::pvData::int32 PvTimeStamp::getUserTag() const
{
    return pvStructurePtr->getIntField(UserTagFieldKey)->get();
}

}}

