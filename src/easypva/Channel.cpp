#include <iostream>

#include "boost/python/extract.hpp"

#include <pv/convert.h>
#include "Channel.h"
#include "pv/logger.h"
#include "PvaException.h"

const char* Channel::DefaultRequestDescriptor("field(value)");
const double Channel::DefaultTimeout(5.0);

using namespace epics::pvData;
using namespace epics::easyPVA;
using namespace std;

static ConvertPtr convert = getConvert();

PvaPyLogger Channel::logger("Channel");

EasyPVAPtr Channel::easyPVA(EasyPVA::create());

Channel::Channel(const std::string& channelName, const string & providerName)
:
    easyChannel(easyPVA->createChannel(channelName,providerName)),
    timeout(DefaultTimeout)
{
    try {
       easyChannel->connect(timeout);
    } catch (std::runtime_error e) {
        string message("channel ");
        message += channelName + " did not connect";
        throw PvaException(message);
    }
}
    

Channel::~Channel()
{
    easyChannel.reset();
}
 
PvObject* Channel::get()
{
    return get(DefaultRequestDescriptor);
}

PvObject* Channel::get(const std::string& requestDescriptor) 
{
    try {
        EasyGetPtr easyGet = easyChannel->createGet(requestDescriptor);
        easyGet->get();
        PVStructurePtr pvStructure = easyGet->getData()->getPVStructure();
        return new PvObject(pvStructure);
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(const PvObject& pvObject)
{
    put(pvObject, DefaultRequestDescriptor);
}

void Channel::put(const PvObject& pvObject, const std::string& requestDescriptor) 
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVStructurePtr pvSend = easyPut->getData()->getPVStructure();
        pvSend << pvObject;
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(const shared_vector<const std::string>& values)
{
    put(values, DefaultRequestDescriptor);
}

void Channel::put(const shared_vector<const std::string>& value, const std::string& requestDescriptor) 
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        EasyPutDataPtr easyData = easyPut->getData();
        easyData->putStringArray(value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(const std::string& value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(const std::string& value, const std::string& requestDescriptor) 
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromString(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(const boost::python::list& pyList, const std::string& requestDescriptor) 
{
    int listSize = boost::python::len(pyList);
    shared_vector<std::string> values(listSize);
    for (int i = 0; i < listSize; i++) {
        values[i] = PyUtility::extractStringFromPyObject(pyList[i]);
    }
    put(freeze(values), requestDescriptor);
}

void Channel::put(const boost::python::list& pyList)
{
    put(pyList, DefaultRequestDescriptor);
}

void Channel::put(bool value, const std::string& requestDescriptor)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVBooleanPtr pv = easyPut->getData()->getPVStructure()->getSubField<PVBoolean>("value");
        if(!pv) throw std::runtime_error("value is not boolean");
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(bool value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(char value, const std::string& requestDescriptor)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromByte(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(char value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(unsigned char value, const std::string& requestDescriptor)
{
    put(StringUtility::toString<int>(static_cast<int>(value)), requestDescriptor);
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromUByte(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(unsigned char value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(short value, const std::string& requestDescriptor)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromShort(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(short value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(unsigned short value, const std::string& requestDescriptor)
{
    put(StringUtility::toString<int>(static_cast<int>(value)), requestDescriptor);
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromUShort(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(unsigned short value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(int value, const std::string& requestDescriptor)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromInt(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(int value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(unsigned int value, const std::string& requestDescriptor)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromUInt(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(unsigned int value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(long long value, const std::string& requestDescriptor)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromLong(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(long long value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(unsigned long long value, const std::string& requestDescriptor)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromULong(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(unsigned long long value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(float value, const std::string& requestDescriptor)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromFloat(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(float value)
{
    put(value, DefaultRequestDescriptor);
}

void Channel::put(double value, const std::string& requestDescriptor)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromDouble(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(double value)
{
    put(value, DefaultRequestDescriptor);
}

