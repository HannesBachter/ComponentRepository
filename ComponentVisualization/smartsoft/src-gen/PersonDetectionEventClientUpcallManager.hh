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
#ifndef _PERSONDETECTIONEVENTCLIENT_UPCALL_MANAGER_HH
#define _PERSONDETECTIONEVENTCLIENT_UPCALL_MANAGER_HH

#include <list>
#include "aceSmartSoft.hh"
#include "PersonDetectionEventClientUpcallInterface.hh"

/** PersonDetectionEventClientUpcallManager connects input-handling with Upcall propagation
 *
 * This class implements an InputHandler for the InputPort personDetectionEventClient and propagates the handling 
 * of incoming data to all associated (i.e. attached) Upcalls.
 */
class PersonDetectionEventClientUpcallManager
:	public Smart::IInputHandler<Smart::EventInputType<CommTrackingObjects::CommPersonDetectionEventResult,SmartACE::EventId>>
{
private:
	// list of associated updalls
	std::list<PersonDetectionEventClientUpcallInterface*> upcalls;

	// call the on_personDetectionEventClient of all the attached PersonDetectionEventClientUpcallInterfaces
	void notify_upcalls(const Smart::EventInputType<CommTrackingObjects::CommPersonDetectionEventResult,SmartACE::EventId> &input);
	
protected:
	virtual void handle_input(const Smart::EventInputType<CommTrackingObjects::CommPersonDetectionEventResult,SmartACE::EventId> &input) {
		// relay input-handling to all attached PersonDetectionEventClientUpcallInterfaces
		this->notify_upcalls(input);
	}
public:
	PersonDetectionEventClientUpcallManager(
		Smart::InputSubject<Smart::EventInputType<CommTrackingObjects::CommPersonDetectionEventResult,SmartACE::EventId>> *subject,
		const int &prescaleFactor=1
	);
	virtual ~PersonDetectionEventClientUpcallManager();
	
	void attach(PersonDetectionEventClientUpcallInterface *upcall);
	void detach(PersonDetectionEventClientUpcallInterface *upcall);
};

#endif
