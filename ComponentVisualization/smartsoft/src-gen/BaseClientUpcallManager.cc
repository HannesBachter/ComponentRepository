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
#include "BaseClientUpcallManager.hh"

BaseClientUpcallManager::BaseClientUpcallManager(
	Smart::InputSubject<CommBasicObjects::CommBaseState> *subject,
	const int &prescaleFactor)
	:	Smart::IInputHandler<CommBasicObjects::CommBaseState>(subject, prescaleFactor)
{  }
BaseClientUpcallManager::~BaseClientUpcallManager()
{  }

void BaseClientUpcallManager::notify_upcalls(const CommBasicObjects::CommBaseState &input)
{
	for(auto it=upcalls.begin(); it!=upcalls.end(); it++) {
		(*it)->on_baseClient(input);
	}
}

void BaseClientUpcallManager::attach(BaseClientUpcallInterface *upcall)
{
	upcalls.push_back(upcall);
}
void BaseClientUpcallManager::detach(BaseClientUpcallInterface *upcall)
{
	upcalls.remove(upcall);
}
