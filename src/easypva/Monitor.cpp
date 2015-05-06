#include "PvObject.h"
#include "PvType.h"
#include "PvaException.h"
#include "PyPvDataUtility.h"
#include "StringUtility.h"
#include "InvalidRequest.h"
#include "InvalidDataType.h"
#include "InvalidArgument.h"
#include "Monitor.h"
#include "boost/python/object.hpp"
#include "boost/python/tuple.hpp"
#include "boost/python/extract.hpp"
#include "boost/python/stl_iterator.hpp"
#include <pv/standardField.h>

using namespace epics::pvData;
using namespace epics::easyPVA;
using namespace std;

namespace epics { namespace pvaPy {

Monitor::Monitor(const Channel &channel)
: easyPVA(channel.getEasyPVA()),
  easyChannel(channel.getEasyChannel())
{
    try {
        easyMonitor = easyChannel->createMonitor("value");
        easyMonitor->connect();
    } catch (std::runtime_error e) {
        string message("channel ");
        throw PvaException(e.what());
    }
    start();
}

Monitor::Monitor(const Channel &channel,const std::string & request)
: easyPVA(channel.getEasyPVA()),
  easyChannel(channel.getEasyChannel())
{
    try {
        easyMonitor = easyChannel->createMonitor(request);
        easyMonitor->connect();
    } catch (std::runtime_error e) {
        string message("channel ");
        throw PvaException(e.what());
    }
    start();
}

Monitor::Monitor(const Channel &channel,const std::string & request,bool autoStart)
: easyPVA(channel.getEasyPVA()),
  easyChannel(channel.getEasyChannel())
{
    try {
        easyMonitor = easyChannel->createMonitor(request);
        easyMonitor->connect();
    } catch (std::runtime_error e) {
        string message("channel ");
        throw PvaException(e.what());
    }
    if(autoStart) start();
}


Monitor::~Monitor()
{
    if(easyMonitor) easyMonitor->stop();
    easyMonitor.reset();
    easyChannel.reset();
    easyPVA.reset();
}

void Monitor::start()
{
    try {
        easyMonitor->start();
    } catch (std::runtime_error e) {
        string message("channel ");
        throw PvaException(e.what());
    }
}

void Monitor::stop()
{
    try {
        easyMonitor->stop();
    } catch (std::runtime_error e) {
        string message("channel ");
        throw PvaException(e.what());
    }
}

bool Monitor::waitEvent(double secondsToWait)
{
    try {
        return easyMonitor->waitEvent(secondsToWait);
    } catch (std::runtime_error e) {
        string message("channel ");
        throw PvaException(e.what());
    }
}

bool Monitor::poll()
{
    try {
        return easyMonitor->poll();
    } catch (std::runtime_error e) {
        string message("channel ");
        throw PvaException(e.what());
    }
}

PvObject* Monitor::getData()
{
    try {
        PvObject* response = new PvObject(easyMonitor->getData()->getPVStructure());
        return response;
    } catch (std::runtime_error e) {
        string message("channel ");
        throw PvaException(e.what());
    }
}

void Monitor::releaseEvent()
{
    try {
        easyMonitor->releaseEvent();
    } catch (std::runtime_error e) {
        string message("channel ");
        throw PvaException(e.what());
    }
}


}}
