#include <iostream>

#include "boost/python/extract.hpp"

#include <pv/convert.h>
#include "Channel.h"
#include "pv/logger.h"
#include "PvaException.h"

namespace epics { namespace pvaPy {

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
        message += channelName + " did not connect " + e.what();
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

void Channel::put(const std::vector<std::string>& values)
{
    put(values, DefaultRequestDescriptor);
}

void Channel::put(const std::vector<std::string>& value, const std::string& requestDescriptor)
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

void Channel::putString(const std::string& value)
{
    putString(value, DefaultRequestDescriptor);
}

void Channel::putString(const std::string& value, const std::string& requestDescriptor) 
{
//cout << "Channel::put(const std::string& value " << "value " << value << endl;
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
    std::vector<std::string> values(listSize);
    for (int i = 0; i < listSize; i++) {
        values[i] = PyUtility::extractStringFromPyObject(pyList[i]);
    }
    put(values, requestDescriptor);
}

void Channel::put(const boost::python::list& pyList)
{
    put(pyList, DefaultRequestDescriptor);
}

void Channel::putBoolean(bool value, const std::string& requestDescriptor)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(requestDescriptor);
        PVBooleanPtr pv = easyPut->getData()->getPVStructure()->getSubField<PVBoolean>("value");
        pv->put(value);
        if(!pv) throw std::runtime_error("value is not boolean");
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putBoolean(bool value)
{
    putBoolean(value, DefaultRequestDescriptor);
}

void Channel::putByte(epics::pvData::int8 value, const std::string& requestDescriptor)
{
//int8 temp = value;
//temp += 1;
//cout << "Channel::put(int8 value "  << "value = " << value << " temp " << temp << endl;
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

void Channel::putByte(epics::pvData::int8 value)
{
    putByte(value, DefaultRequestDescriptor);
}

void Channel::putUByte(uint8 value, const std::string& requestDescriptor)
{
//cout << "Channel::put(uint8 value "  << "value = " << value << endl;
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

void Channel::putUByte(uint8 value)
{
    putUByte(value, DefaultRequestDescriptor);
}

void Channel::putShort(int16 value, const std::string& requestDescriptor)
{
//cout << "Channel::put(int16 value "  << "value = " << value << endl;
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

void Channel::putShort(int16 value)
{
    putShort(value, DefaultRequestDescriptor);
}

void Channel::putUShort(uint16 value, const std::string& requestDescriptor)
{
//cout << "Channel::put(uint16 value "  << "value = " << value << endl;
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

void Channel::putUShort(uint16 value)
{
    putUShort(value, DefaultRequestDescriptor);
}

void Channel::putInt(int32 value, const std::string& requestDescriptor)
{
//cout << "Channel::put(int32 value "  << "value = " << value << endl;
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

void Channel::putInt(int32 value)
{
    putInt(value, DefaultRequestDescriptor);
}

void Channel::putUInt(uint32 value, const std::string& requestDescriptor)
{
//cout << "Channel::put(uint32 value "  << "value = " << value << endl;
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

void Channel::putUInt(uint32 value)
{
    putUInt(value, DefaultRequestDescriptor);
}

void Channel::putLong(int64 value, const std::string& requestDescriptor)
{
//cout << "Channel::put(int64 value "  << "value = " << value << endl;
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

void Channel::putLong(int64 value)
{
    putLong(value, DefaultRequestDescriptor);
}

void Channel::putULong(uint64 value, const std::string& requestDescriptor)
{
//cout << "Channel::put(uint64 value "  << "value = " << value << endl;
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

void Channel::putULong(uint64 value)
{
    putULong(value, DefaultRequestDescriptor);
}

void Channel::putFloat(float value, const std::string& requestDescriptor)
{
//cout << "Channel::put(float value "  << "value = " << value << endl;
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

void Channel::putFloat(float value)
{
    putFloat(value, DefaultRequestDescriptor);
}

void Channel::putDouble(double value, const std::string& requestDescriptor)
{
//cout << "Channel::put(double value "  << "value = " << value << endl;
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

void Channel::putDouble(double value)
{
    putDouble(value, DefaultRequestDescriptor);
}

}}
