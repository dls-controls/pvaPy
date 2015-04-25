#include <iostream>

#include "boost/python/extract.hpp"

#include <pv/convert.h>
#include "Channel.h"
#include "pv/logger.h"
#include "PvaException.h"

namespace epics { namespace pvaPy {

const char* Channel::DefaultRequest("field(value)");
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


PvObject* Channel::getObject(const std::string& request) 
{
    try {
        EasyGetPtr easyGet = easyChannel->createGet(request);
        easyGet->get();
        PVStructurePtr pvStructure = easyGet->getData()->getPVStructure();
        return new PvObject(pvStructure);
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putObject(const PvObject& pvObject, const std::string& request) 
{
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVStructurePtr pvSend = easyPut->getData()->getPVStructure();
        pvSend << pvObject;
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::put(const std::vector<std::string>& value, const std::string& request)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        EasyPutDataPtr easyData = easyPut->getData();
        easyData->putStringArray(value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putString(const std::string& value, const std::string& request) 
{
//cout << "Channel::put(const std::string& value " << "value " << value << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromString(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putList(const boost::python::list& pyList, const std::string& request) 
{
    int listSize = boost::python::len(pyList);
    std::vector<std::string> values(listSize);
    for (int i = 0; i < listSize; i++) {
        values[i] = PyUtility::extractStringFromPyObject(pyList[i]);
    }
    put(values, request);
}


void Channel::putBoolean(bool value, const std::string& request)
{
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
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


void Channel::putByte(epics::pvData::int8 value, const std::string& request)
{
//int8 temp = value;
//temp += 1;
//cout << "Channel::put(int8 value "  << "value = " << value << " temp " << temp << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromByte(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putUByte(uint8 value, const std::string& request)
{
//cout << "Channel::put(uint8 value "  << "value = " << value << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromUByte(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putShort(int16 value, const std::string& request)
{
//cout << "Channel::put(int16 value "  << "value = " << value << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromShort(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putUShort(uint16 value, const std::string& request)
{
//cout << "Channel::put(uint16 value "  << "value = " << value << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromUShort(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putInt(int32 value, const std::string& request)
{
//cout << "Channel::putInt(int32 value "  << "value = " << value << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromInt(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putUInt(uint32 value, const std::string& request)
{
//cout << "Channel::put(uint32 value "  << "value = " << value << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromUInt(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putLong(int64 value, const std::string& request)
{
//cout << "Channel::putLong(int64 value "  << "value = " << value << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromLong(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putULong(uint64 value, const std::string& request)
{
//cout << "Channel::put(uint64 value "  << "value = " << value << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromULong(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putFloat(float value, const std::string& request)
{
//cout << "Channel::put(float value "  << "value = " << value << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromFloat(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

void Channel::putDouble(double value, const std::string& request)
{
//cout << "Channel::putDouble(double value "  << "value = " << value << endl;
    try {
        EasyPutPtr easyPut = easyChannel->put(request);
        PVScalarPtr pvScalar = easyPut->getData()->getScalarValue();
        convert->fromDouble(pvScalar,value);
        easyPut->put();
    } catch (std::runtime_error e) {
        string message("channel ");
        message += easyChannel->getChannelName() + " error " + e.what();
        throw PvaException(message);
    }
}

}}
