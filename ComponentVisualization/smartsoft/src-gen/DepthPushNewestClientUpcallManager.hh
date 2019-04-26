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
#ifndef _DEPTHPUSHNEWESTCLIENT_UPCALL_MANAGER_HH
#define _DEPTHPUSHNEWESTCLIENT_UPCALL_MANAGER_HH

#include <list>
#include "aceSmartSoft.hh"
#include "DepthPushNewestClientUpcallInterface.hh"

/** DepthPushNewestClientUpcallManager connects input-handling with Upcall propagation
 *
 * This class implements an InputHandler for the InputPort depthPushNewestClient and propagates the handling 
 * of incoming data to all associated (i.e. attached) Upcalls.
 */
class DepthPushNewestClientUpcallManager
:	public Smart::IInputHandler<DomainVision::CommDepthImage>
{
private:
	// list of associated updalls
	std::list<DepthPushNewestClientUpcallInterface*> upcalls;

	// call the on_depthPushNewestClient of all the attached DepthPushNewestClientUpcallInterfaces
	void notify_upcalls(const DomainVision::CommDepthImage &input);
	
protected:
	virtual void handle_input(const DomainVision::CommDepthImage &input) {
		// relay input-handling to all attached DepthPushNewestClientUpcallInterfaces
		this->notify_upcalls(input);
	}
public:
	DepthPushNewestClientUpcallManager(
		Smart::InputSubject<DomainVision::CommDepthImage> *subject,
		const int &prescaleFactor=1
	);
	virtual ~DepthPushNewestClientUpcallManager();
	
	void attach(DepthPushNewestClientUpcallInterface *upcall);
	void detach(DepthPushNewestClientUpcallInterface *upcall);
};

#endif
