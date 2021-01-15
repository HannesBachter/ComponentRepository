//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#ifndef _ROBOTDOCKINGEVENTSERVICEOUTWRAPPER_HH
#define _ROBOTDOCKINGEVENTSERVICEOUTWRAPPER_HH

#include <mutex>
#include "aceSmartSoft.hh"

// include communication objects
#include <CommNavigationObjects/CommDockingEventParameter.hh>
#include <CommNavigationObjects/CommDockingEventParameterACE.hh>
#include <CommNavigationObjects/CommDockingEventResult.hh>
#include <CommNavigationObjects/CommDockingEventResultACE.hh>
#include <CommNavigationObjects/CommDockingEventState.hh>
#include <CommNavigationObjects/CommDockingEventStateACE.hh>


class RobotDockingEventServiceOutWrapper
{
private:
	std::mutex update_mutex;
	Smart::StatusCode update_status;
	
	CommNavigationObjects::CommDockingEventState updateEventState;
	CommNavigationObjects::CommDockingEventResult updateEvent;
	CommNavigationObjects::CommDockingEventParameter updateActivation;
	
	Smart::IEventServerPattern<CommNavigationObjects::CommDockingEventParameter, CommNavigationObjects::CommDockingEventResult, CommNavigationObjects::CommDockingEventState> *robotDockingEventServiceOut;
	
public:
	RobotDockingEventServiceOutWrapper(Smart::IEventServerPattern<CommNavigationObjects::CommDockingEventParameter, CommNavigationObjects::CommDockingEventResult, CommNavigationObjects::CommDockingEventState> *robotDockingEventServiceOut);
	virtual ~RobotDockingEventServiceOutWrapper();
	
	Smart::StatusCode put(CommNavigationObjects::CommDockingEventState &eventState);
	
	Smart::StatusCode getLatestUpdate(CommNavigationObjects::CommDockingEventState &eventState);
	
};

#endif // _ROBOTDOCKINGEVENTSERVICEOUTWRAPPER_HH