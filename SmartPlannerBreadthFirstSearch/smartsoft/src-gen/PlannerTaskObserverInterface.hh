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
#ifndef _PLANNERTASK_OBSERVER_INTERFACE_HH
#define _PLANNERTASK_OBSERVER_INTERFACE_HH

// forward declaration
class PlannerTask;

class PlannerTaskObserverInterface {
public:
	virtual ~PlannerTaskObserverInterface() {  }

	virtual void on_update_from(const PlannerTask *subject) = 0;
};

#endif
