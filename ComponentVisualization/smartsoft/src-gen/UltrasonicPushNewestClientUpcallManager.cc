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
#include "UltrasonicPushNewestClientUpcallManager.hh"

UltrasonicPushNewestClientUpcallManager::UltrasonicPushNewestClientUpcallManager(
	Smart::InputSubject<CommBasicObjects::CommMobileUltrasonicScan> *subject,
	const int &prescaleFactor)
	:	Smart::IInputHandler<CommBasicObjects::CommMobileUltrasonicScan>(subject, prescaleFactor)
{  }
UltrasonicPushNewestClientUpcallManager::~UltrasonicPushNewestClientUpcallManager()
{  }

void UltrasonicPushNewestClientUpcallManager::notify_upcalls(const CommBasicObjects::CommMobileUltrasonicScan &input)
{
	for(auto it=upcalls.begin(); it!=upcalls.end(); it++) {
		(*it)->on_ultrasonicPushNewestClient(input);
	}
}

void UltrasonicPushNewestClientUpcallManager::attach(UltrasonicPushNewestClientUpcallInterface *upcall)
{
	upcalls.push_back(upcall);
}
void UltrasonicPushNewestClientUpcallManager::detach(UltrasonicPushNewestClientUpcallInterface *upcall)
{
	upcalls.remove(upcall);
}
