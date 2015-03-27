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

class Channel
{
public:

    static const char* DefaultRequestDescriptor;
    static const double DefaultTimeout;
        
    Channel(const std::string& channelName, const std::string& providerName = "pva");
    virtual ~Channel();

    std::string getName() const;
    virtual PvObject* get(const std::string& requestDescriptor);
    virtual PvObject* get();
    virtual void put(const PvObject& pvObject, const std::string& requestDescriptor);
    virtual void put(const PvObject& pvObject);
    virtual void put(const std::vector<std::string>& values, const std::string& requestDescriptor);
    virtual void put(const std::vector<std::string>& values);
    virtual void put(const std::string& value, const std::string& requestDescriptor);
    virtual void put(const std::string& value);
    virtual void put(const boost::python::list& pyList, const std::string& requestDescriptor);
    virtual void put(const boost::python::list& pyList);

    virtual void put(bool value, const std::string& requestDescriptor);
    virtual void put(bool value);
    virtual void put(char value, const std::string& requestDescriptor);
    virtual void put(char value);
    virtual void put(unsigned char value, const std::string& requestDescriptor);
    virtual void put(unsigned char value);
    virtual void put(short value, const std::string& requestDescriptor);
    virtual void put(short value);
    virtual void put(unsigned short value, const std::string& requestDescriptor);
    virtual void put(unsigned short value);
    virtual void put(int value, const std::string& requestDescriptor);
    virtual void put(int value);
    virtual void put(unsigned int value, const std::string& requestDescriptor);
    virtual void put(unsigned int value);
    virtual void put(long long value, const std::string& requestDescriptor);
    virtual void put(long long value);
    virtual void put(unsigned long long value, const std::string& requestDescriptor);
    virtual void put(unsigned long long value);
    virtual void put(float value, const std::string& requestDescriptor);
    virtual void put(float value);
    virtual void put(double value, const std::string& requestDescriptor);
    virtual void put(double value);

    virtual void setTimeout(double timeout);
    virtual double getTimeout() const;
    epics::easyPVA::EasyChannelPtr getEasyChannel();
    epics::easyPVA::EasyPVAPtr getEasyPVA();

private:
    static PvaPyLogger logger;
    static epics::easyPVA::EasyPVAPtr easyPVA;

    epics::easyPVA::EasyChannelPtr easyChannel;
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

#endif
