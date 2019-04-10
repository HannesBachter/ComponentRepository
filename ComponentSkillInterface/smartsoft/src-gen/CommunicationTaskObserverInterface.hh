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
#ifndef _COMMUNICATIONTASK_OBSERVER_INTERFACE_HH
#define _COMMUNICATIONTASK_OBSERVER_INTERFACE_HH

// forward declaration
class CommunicationTask;

class CommunicationTaskObserverInterface {
public:
	virtual ~CommunicationTaskObserverInterface() {  }

	virtual void on_update_from(const CommunicationTask *subject) = 0;
};

#endif
