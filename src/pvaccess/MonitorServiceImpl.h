/*
 * MonitorServiceImpl.h
 *
 *  Created on: 31 Aug 2016
 *      Author: gnx91527
 */

#ifndef SRC_PVACCESS_MONITORSERVICEIMPL_H_
#define SRC_PVACCESS_MONITORSERVICEIMPL_H_

#include "pv/pvData.h"
#include "pv/pvAccess.h"
#include "pv/pvaServer.h"
#include "boost/python/object.hpp"


class MonitorServiceImpl : public epics::pvLocal::MonitorService,
    public std::tr1::enable_shared_from_this<MonitorServiceImpl>
{
	public:
		POINTER_DEFINITIONS(MonitorServiceImpl);
		MonitorServiceImpl(const boost::python::object& pyService);

        void init();

        virtual void addListener(epics::pvLocal::MonitorServiceListenerPtr const & listener);
		virtual ~MonitorServiceImpl();
		epics::pvData::PVStructurePtr getPVStructure();

        void update() { if (listener.get()) listener->update();}

	private:
	    boost::python::object pyService;
        epics::pvLocal::MonitorServiceListenerPtr listener;
};

//class MonitorServiceImpl;
typedef std::tr1::shared_ptr<MonitorServiceImpl> MonitorServiceImplPtr;

class MonitorServiceUpdater
{
public:
    MonitorServiceUpdater() {}

    virtual void update()
    {
        if (x.get()) x->update();
    }

    virtual void registerMonitorService(MonitorServiceImplPtr const & xx)
    {
        x = xx;
    }

private:
    MonitorServiceImplPtr x;
};


#endif /* SRC_PVACCESS_MONITORSERVICEIMPL_H_ */
