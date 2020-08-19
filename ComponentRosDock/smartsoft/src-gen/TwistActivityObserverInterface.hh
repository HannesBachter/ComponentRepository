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
#ifndef _TWISTACTIVITY_OBSERVER_INTERFACE_HH
#define _TWISTACTIVITY_OBSERVER_INTERFACE_HH

// forward declaration
class TwistActivity;

class TwistActivityObserverInterface {
public:
	virtual ~TwistActivityObserverInterface() {  }

	virtual void on_update_from(const TwistActivity *subject) = 0;
};

#endif