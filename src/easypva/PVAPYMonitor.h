#ifndef PVAPYMONITOR_H
#define PVAPYMONITOR_H

#include <string>
#include <vector>
#include <pv/easyPVA.h>

#include "boost/python/list.hpp"

#include "PyUtility.h"
#include "StringUtility.h"
#include "PvaPyLogger.h"
#include "Channel.h"

namespace epics { namespace pvaPy {

class PVAPYMonitor;
typedef std::tr1::shared_ptr<PVAPYMonitor> PVAPYMonitorPtr;

class PVAPYMonitor
{
public:
    PVAPYMonitor(const Channel &channel);
    PVAPYMonitor(const Channel &channel,const std::string & request);
    PVAPYMonitor(const Channel &channel,const std::string & request,bool autoStart);
    ~PVAPYMonitor();
    void start();
    void stop();
    bool waitEvent(double secondsToWait = 0.0);
    bool poll();
    PvObject* getData();
    void releaseEvent();
private:
    epics::easyPVA::EasyPVAPtr easyPVA;
    epics::easyPVA::EasyChannelPtr easyChannel;
    epics::easyPVA::EasyMonitorPtr easyMonitor;
    boost::python::object pySubscriber;
};

}}

#endif
