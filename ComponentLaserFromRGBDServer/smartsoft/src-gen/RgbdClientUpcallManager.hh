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
#ifndef _RGBDCLIENT_UPCALL_MANAGER_HH
#define _RGBDCLIENT_UPCALL_MANAGER_HH

#include <list>
#include "aceSmartSoft.hh"
#include "RgbdClientUpcallInterface.hh"

/** RgbdClientUpcallManager connects input-handling with Upcall propagation
 *
 * This class implements an InputHandler for the InputPort rgbdClient and propagates the handling 
 * of incoming data to all associated (i.e. attached) Upcalls.
 */
class RgbdClientUpcallManager
:	public Smart::IInputHandler<DomainVision::CommRGBDImage>
{
private:
	// list of associated updalls
	std::list<RgbdClientUpcallInterface*> upcalls;

	// call the on_rgbdClient of all the attached RgbdClientUpcallInterfaces
	void notify_upcalls(const DomainVision::CommRGBDImage &input);
	
protected:
	virtual void handle_input(const DomainVision::CommRGBDImage &input) {
		// relay input-handling to all attached RgbdClientUpcallInterfaces
		this->notify_upcalls(input);
	}
public:
	RgbdClientUpcallManager(
		Smart::InputSubject<DomainVision::CommRGBDImage> *subject,
		const int &prescaleFactor=1
	);
	virtual ~RgbdClientUpcallManager();
	
	void attach(RgbdClientUpcallInterface *upcall);
	void detach(RgbdClientUpcallInterface *upcall);
};

#endif
