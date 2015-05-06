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

class Monitor;
typedef std::tr1::shared_ptr<Monitor> MonitorPtr;

class Monitor
{
public:
    Monitor(const Channel &channel);
    Monitor(const Channel &channel,const std::string & request);
    Monitor(const Channel &channel,const std::string & request,bool autoStart);
    ~Monitor();
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
