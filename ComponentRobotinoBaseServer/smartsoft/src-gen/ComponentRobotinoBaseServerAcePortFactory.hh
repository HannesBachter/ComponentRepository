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

#ifndef COMPONENTROBOTINOBASESERVER_ACE_PORTFACTORY_HH_
#define COMPONENTROBOTINOBASESERVER_ACE_PORTFACTORY_HH_

// include ACE/SmartSoft component implementation
#include "ComponentRobotinoBaseServerImpl.hh"

// include the main component-definition class
#include "ComponentRobotinoBaseServerPortFactoryInterface.hh"

class ComponentRobotinoBaseServerAcePortFactory: public ComponentRobotinoBaseServerPortFactoryInterface
{
private:
	ComponentRobotinoBaseServerImpl *componentImpl;
public:
	ComponentRobotinoBaseServerAcePortFactory();
	virtual ~ComponentRobotinoBaseServerAcePortFactory();

	virtual void initialize(ComponentRobotinoBaseServer *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	virtual Smart::IEventClientPattern<CommLocalizationObjects::CommLocalizationEventParameter, CommLocalizationObjects::CommLocalizationEventResult,SmartACE::EventId> * createLocalizationEventServiceIn() override;
	
	virtual Smart::IQueryServerPattern<CommBasicObjects::CommVoid, CommBasicObjects::CommBaseState,SmartACE::QueryId> * createBaseStateQueryServiceAnsw(const std::string &serviceName) override;
	virtual Smart::IPushServerPattern<CommBasicObjects::CommBaseState> * createBaseStateServiceOut(const std::string &serviceName) override;
	virtual Smart::IEventServerPattern<CommBasicObjects::CommBatteryParameter, CommBasicObjects::CommBatteryEvent, CommBasicObjects::CommBatteryState,SmartACE::EventId> * createBatteryEventServiceOut(const std::string &serviceName, Smart::IEventTestHandler<CommBasicObjects::CommBatteryParameter, CommBasicObjects::CommBatteryEvent, CommBasicObjects::CommBatteryState> *batteryEventServiceOutEventTestHandler) override;
	virtual Smart::IEventServerPattern<CommBasicObjects::CommBumperEventParameter, CommBasicObjects::CommBumperEventResult, CommBasicObjects::CommBumperEventState,SmartACE::EventId> * createBumperEventServiceOut(const std::string &serviceName, Smart::IEventTestHandler<CommBasicObjects::CommBumperEventParameter, CommBasicObjects::CommBumperEventResult, CommBasicObjects::CommBumperEventState> *bumperEventServiceOutEventTestHandler) override;
	virtual Smart::IEventServerPattern<CommRobotinoObjects::CommDigitalInputEventParameter, CommRobotinoObjects::CommDigitalInputEventResult, CommRobotinoObjects::CommDigitalInputEventState,SmartACE::EventId> * createDigitalInputEventOut(const std::string &serviceName, Smart::IEventTestHandler<CommRobotinoObjects::CommDigitalInputEventParameter, CommRobotinoObjects::CommDigitalInputEventResult, CommRobotinoObjects::CommDigitalInputEventState> *digitalInputEventOutEventTestHandler) override;
	virtual Smart::IEventServerPattern<CommBasicObjects::CommLaserSafetyEventParam, CommBasicObjects::CommLaserSafetyField, CommBasicObjects::CommLaserSafetyEventState,SmartACE::EventId> * createLaserSafetyEventServiceOut(const std::string &serviceName, Smart::IEventTestHandler<CommBasicObjects::CommLaserSafetyEventParam, CommBasicObjects::CommLaserSafetyField, CommBasicObjects::CommLaserSafetyEventState> *laserSafetyEventServiceOutEventTestHandler) override;
	virtual Smart::ISendServerPattern<CommBasicObjects::CommBasePositionUpdate> * createLocalizationUpdateServiceIn(const std::string &serviceName) override;
	virtual Smart::ISendServerPattern<CommBasicObjects::CommNavigationVelocity> * createNavigationVelocityServiceIn(const std::string &serviceName) override;
	virtual Smart::ISendServerPattern<CommRobotinoObjects::CommRobotinoPowerOutputValue> * createPowerOutputSendIn(const std::string &serviceName) override;
	virtual Smart::IQueryServerPattern<CommRobotinoObjects::CommRobotinoIOValues, CommRobotinoObjects::CommRobotinoIOValues,SmartACE::QueryId> * createRobotinoIOValuesQueryServiceAnsw(const std::string &serviceName) override;
	
	// get a pointer to the internal component implementation
	SmartACE::SmartComponent* getComponentImpl();

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* COMPONENTROBOTINOBASESERVER_ACE_PORTFACTORY_HH_ */
