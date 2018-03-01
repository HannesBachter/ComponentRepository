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
#ifndef _BASESTATEIN_UPCALL_MANAGER_HH
#define _BASESTATEIN_UPCALL_MANAGER_HH

#include <list>
#include "aceSmartSoft.hh"
#include "BaseStateInUpcallInterface.hh"

/** BaseStateInUpcallManager connects input-handling with Upcall propagation
 *
 * This class implements an InputHandler for the InputPort BaseStateIn and propagates the handling 
 * of incoming data to all associated (i.e. attached) Upcalls.
 */
class BaseStateInUpcallManager
:	public Smart::IInputHandler<CommBasicObjects::CommBaseState>
{
private:
	// list of associated updalls
	std::list<BaseStateInUpcallInterface*> upcalls;

	// call the on_BaseStateIn of all the attached BaseStateInUpcallInterfaces
	void notify_upcalls(const CommBasicObjects::CommBaseState &input);
	
protected:
	virtual void handle_input(const CommBasicObjects::CommBaseState &input) {
		// relay input-handling to all attached BaseStateInUpcallInterfaces
		this->notify_upcalls(input);
	}
public:
	BaseStateInUpcallManager(
		Smart::InputSubject<CommBasicObjects::CommBaseState> *subject,
		const int &prescaleFactor=1
	);
	virtual ~BaseStateInUpcallManager();
	
	void attach(BaseStateInUpcallInterface *upcall);
	void detach(BaseStateInUpcallInterface *upcall);
};

#endif
