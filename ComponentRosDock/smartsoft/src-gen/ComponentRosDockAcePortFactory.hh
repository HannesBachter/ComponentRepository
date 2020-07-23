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

#ifndef COMPONENTROSDOCK_ACE_PORTFACTORY_HH_
#define COMPONENTROSDOCK_ACE_PORTFACTORY_HH_

// include ACE/SmartSoft component implementation
#include "ComponentRosDockImpl.hh"

// include the main component-definition class
#include "ComponentRosDockPortFactoryInterface.hh"

class ComponentRosDockAcePortFactory: public ComponentRosDockPortFactoryInterface
{
private:
	ComponentRosDockImpl *componentImpl;
public:
	ComponentRosDockAcePortFactory();
	virtual ~ComponentRosDockAcePortFactory();

	virtual void initialize(ComponentRosDock *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	
	virtual Smart::IPushServerPattern<CommBasicObjects::CommBaseState> * createBaseStateServiceOut(const std::string &serviceName) override;
	
	// get a pointer to the internal component implementation
	SmartACE::SmartComponent* getComponentImpl();

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* COMPONENTROSDOCK_ACE_PORTFACTORY_HH_ */
