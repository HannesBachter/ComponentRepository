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

#ifndef COMPONENTSKILLINTERFACE_PORTFACTORYINTERFACE_HH_
#define COMPONENTSKILLINTERFACE_PORTFACTORYINTERFACE_HH_

// include communication objects
#include <CommBasicObjects/CommKBRequest.hh>
#include <CommBasicObjects/CommKBRequestACE.hh>
#include <CommBasicObjects/CommKBResponse.hh>
#include <CommBasicObjects/CommKBResponseACE.hh>

#include <chrono>

// include component's main class
#include "ComponentSkillInterface.hh"

// forward declaration
class ComponentSkillInterface;

class ComponentSkillInterfacePortFactoryInterface {
public:
	ComponentSkillInterfacePortFactoryInterface() { };
	virtual ~ComponentSkillInterfacePortFactoryInterface() { };

	virtual void initialize(ComponentSkillInterface *component, int argc, char* argv[]) = 0;
	virtual int onStartup() = 0;

	virtual Smart::IQueryClientPattern<CommBasicObjects::CommKBRequest, CommBasicObjects::CommKBResponse,SmartACE::QueryId> * createKBQueryClient() = 0;
	

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) = 0;
	virtual void destroy() = 0;
};

#endif /* COMPONENTSKILLINTERFACE_PORTFACTORYINTERFACE_HH_ */
