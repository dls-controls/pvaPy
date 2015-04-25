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

    static const char* DefaultRequest;
    static const double DefaultTimeout;
        
    Channel(const std::string& channelName, const std::string& providerName = "pva");
    ~Channel();

    std::string getName() const;
    PvObject* getObject(const std::string& request);
    void putObject(const PvObject& pvObject, const std::string& request);
    void putList(const boost::python::list& pyList, const std::string& request);
    void putString(const std::string& value, const std::string& request);
    void putBoolean(bool value, const std::string& request);
    void putByte(epics::pvData::int8 value, const std::string& request);
    void putUByte(epics::pvData::uint8 value, const std::string& request);
    void putShort(epics::pvData::int16 value, const std::string& request);
    void putUShort(epics::pvData::uint16 value, const std::string& request);
    void putInt(epics::pvData::int32 value, const std::string& request);
    void putUInt(epics::pvData::uint32 value, const std::string& request);
    void putLong(epics::pvData::int64 value, const std::string& request);
    void putULong(epics::pvData::uint64 value, const std::string& request);
    void putFloat(float value, const std::string& request);
    void putDouble(double value, const std::string& request);

    void setTimeout(double timeout);
    double getTimeout() const;
    epics::easyPVA::EasyChannelPtr getEasyChannel() const;
    static epics::easyPVA::EasyPVAPtr getEasyPVA() ;

private:
    void put(
        const std::vector<std::string>& values,
        const std::string& request);
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
