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
#ifndef _BASEFAKEACTIVITY_CORE_HH
#define _BASEFAKEACTIVITY_CORE_HH
	
#include "aceSmartSoft.hh"

// include upcall interface
#include "NavigationVelocityServiceInUpcallInterface.hh"

// include communication-objects for output ports
#include <CommBasicObjects/CommBaseState.hh>

// include all interaction-observer interfaces
#include <BaseFakeActivityObserverInterface.hh>

#include <geometry_msgs/Twist.h>

class BaseFakeActivityCore
:	public SmartACE::ManagedTask
,	public Smart::TaskTriggerSubject
,	public NavigationVelocityServiceInUpcallInterface
{
private:
	bool useDefaultState; 
	bool useLogging;
	int taskLoggingId;
	unsigned int currentUpdateCount;
	
	Smart::StatusCode navigationVelocityServiceInStatus;
	CommBasicObjects::CommNavigationVelocity navigationVelocityServiceInObject;
	
	
protected:
	virtual int execute_protected_region();
	
	virtual void updateAllCommObjects();
	
	virtual int getPreviousCommObjId();
	
	void triggerLogEntry(const int& idOffset);
	
	
	// overload and implement this method in derived classes to immediately get all incoming updates from NavigationVelocityServiceIn (as soon as they arrive)
	virtual void on_NavigationVelocityServiceIn(const CommBasicObjects::CommNavigationVelocity &input) {
		// no-op
	}
	
	// this method can be safely used from the thread in derived classes
	inline Smart::StatusCode navigationVelocityServiceInGetUpdate(CommBasicObjects::CommNavigationVelocity &navigationVelocityServiceInObject) const
	{
		// copy local object buffer and return the last status code
		navigationVelocityServiceInObject = this->navigationVelocityServiceInObject;
		return navigationVelocityServiceInStatus;
	}
	
	// this method is meant to be used in derived classes
	Smart::StatusCode baseStateServiceOutPut(CommBasicObjects::CommBaseState &baseStateServiceOutDataObject);
	
	
/**
 * Implementation of the Subject part of an InteractionObserver
 */
private:
	std::mutex interaction_observers_mutex;
	std::list<BaseFakeActivityObserverInterface*> interaction_observers;
protected:
	void notify_all_interaction_observers();
public:
	void attach_interaction_observer(BaseFakeActivityObserverInterface *observer);
	void detach_interaction_observer(BaseFakeActivityObserverInterface *observer);

public:
	BaseFakeActivityCore(Smart::IComponent *comp, const bool &useDefaultState=true);
	virtual ~BaseFakeActivityCore();
	
	inline void setUpLogging(const int &taskNbr, const bool &useLogging=true) {
		this->taskLoggingId = taskNbr;
		this->useLogging = useLogging;
	}
	
	inline bool isLoggingActive() const {
		return useLogging;
	}
	
	inline int getLoggingID() const {
		return taskLoggingId;
	}
	
	inline int getCurrentUpdateCount() const {
		return currentUpdateCount;
	}
	
};
#endif