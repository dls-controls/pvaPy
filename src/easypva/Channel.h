#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <vector>
#include <pv/easyPVA.h>

#include "boost/python/list.hpp"

#include "PyUtility.h"
#include "StringUtility.h"
#include "PvObject.h"
#include "PvaPyLogger.h"

namespace epics { namespace pvaPy {

class Channel
{
public:

    static const char* DefaultRequestDescriptor;
    static const double DefaultTimeout;
        
    Channel(const std::string& channelName, const std::string& providerName = "pva");
    ~Channel();

    std::string getName() const;
    PvObject* get(const std::string& requestDescriptor);
    PvObject* get();
    void put(const PvObject& pvObject, const std::string& requestDescriptor);
    void put(const PvObject& pvObject);
    void put(const boost::python::list& pyList, const std::string& requestDescriptor);
    void put(const boost::python::list& pyList);

    void putString(const std::string& value, const std::string& requestDescriptor);
    void putString(const std::string& value);
    void putBoolean(bool value, const std::string& requestDescriptor);
    void putBoolean(bool value);
    void putByte(epics::pvData::int8 value, const std::string& requestDescriptor);
    void putByte(epics::pvData::int8 value);
    void putUByte(epics::pvData::uint8 value, const std::string& requestDescriptor);
    void putUByte(epics::pvData::uint8 value);
    void putShort(epics::pvData::int16 value, const std::string& requestDescriptor);
    void putShort(epics::pvData::int16 value);
    void putUShort(epics::pvData::uint16 value, const std::string& requestDescriptor);
    void putUShort(epics::pvData::uint16 value);
    void putInt(epics::pvData::int32 value, const std::string& requestDescriptor);
    void putInt(epics::pvData::int32 value);
    void putUInt(epics::pvData::uint32 value, const std::string& requestDescriptor);
    void putUInt(epics::pvData::uint32 value);
    void putLong(epics::pvData::int64 value, const std::string& requestDescriptor);
    void putLong(epics::pvData::int64 value);
    void putULong(epics::pvData::uint64 value, const std::string& requestDescriptor);
    void putULong(epics::pvData::uint64 value);
    void putFloat(float value, const std::string& requestDescriptor);
    void putFloat(float value);
    void putDouble(double value, const std::string& requestDescriptor);
    void putDouble(double value);

    void setTimeout(double timeout);
    double getTimeout() const;
    epics::easyPVA::EasyChannelPtr getEasyChannel() const;
    static epics::easyPVA::EasyPVAPtr getEasyPVA() ;

private:
    void put(
        const std::vector<std::string>& values,
        const std::string& requestDescriptor);
    void put(const std::vector<std::string>& values);
    static PvaPyLogger logger;
    static epics::easyPVA::EasyPVAPtr easyPVA;
    epics::easyPVA::EasyChannelPtr  easyChannel;

    double timeout;
};

inline std::string Channel::getName() const
{
    return easyChannel->getChannelName();
}

inline void Channel::setTimeout(double timeout) 
{
    this->timeout = timeout;
}

inline double Channel::getTimeout() const
{
    return timeout;
}

inline epics::easyPVA::EasyChannelPtr Channel::getEasyChannel() const
{
    return easyChannel;
}

inline epics::easyPVA::EasyPVAPtr Channel::getEasyPVA() 
{
    return easyPVA;
}

}}
#endif
