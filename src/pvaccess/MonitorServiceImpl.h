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

class MonitorServiceImpl : public epics::pvLocal::MonitorService
{
	public:
		POINTER_DEFINITIONS(MonitorServiceImpl);
		MonitorServiceImpl(const boost::python::object& pyService);
		virtual ~MonitorServiceImpl();
		epics::pvData::PVStructurePtr getPVStructure();

	private:
	    boost::python::object pyService;
};

typedef std::tr1::shared_ptr<MonitorServiceImpl> MonitorServiceImplPtr;

#endif /* SRC_PVACCESS_MONITORSERVICEIMPL_H_ */
