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
#include "UrPosePushTimedClientUpcallManager.hh"

UrPosePushTimedClientUpcallManager::UrPosePushTimedClientUpcallManager(
	Smart::InputSubject<CommManipulatorObjects::CommMobileManipulatorState> *subject,
	const int &prescaleFactor)
	:	Smart::IInputHandler<CommManipulatorObjects::CommMobileManipulatorState>(subject, prescaleFactor)
{  }
UrPosePushTimedClientUpcallManager::~UrPosePushTimedClientUpcallManager()
{  }

void UrPosePushTimedClientUpcallManager::notify_upcalls(const CommManipulatorObjects::CommMobileManipulatorState &input)
{
	for(auto it=upcalls.begin(); it!=upcalls.end(); it++) {
		(*it)->on_UrPosePushTimedClient(input);
	}
}

void UrPosePushTimedClientUpcallManager::attach(UrPosePushTimedClientUpcallInterface *upcall)
{
	upcalls.push_back(upcall);
}
void UrPosePushTimedClientUpcallManager::detach(UrPosePushTimedClientUpcallInterface *upcall)
{
	upcalls.remove(upcall);
}
