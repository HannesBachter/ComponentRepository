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
#ifndef _COMPONENTPLAYERSTAGESIMULATOR_HH
#define _COMPONENTPLAYERSTAGESIMULATOR_HH

#include <map>
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "ComponentPlayerStageSimulatorCore.hh"

#include "ComponentPlayerStageSimulatorPortFactoryInterface.hh"
#include "ComponentPlayerStageSimulatorExtension.hh"

// forward declarations
class ComponentPlayerStageSimulatorPortFactoryInterface;
class ComponentPlayerStageSimulatorExtension;

// includes for ComponentPlayerStageSimulatorROSExtension

// includes for PlainOpcUaComponentPlayerStageSimulatorExtension
// include plain OPC UA device clients
// include plain OPC UA status servers


// include communication objects
#include <CommBasicObjects/CommBasePositionUpdate.hh>
#include <CommBasicObjects/CommBasePositionUpdateACE.hh>
#include <CommBasicObjects/CommBaseState.hh>
#include <CommBasicObjects/CommBaseStateACE.hh>
#include <CommBasicObjects/CommBatteryEvent.hh>
#include <CommBasicObjects/CommBatteryEventACE.hh>
#include <CommBasicObjects/CommBatteryParameter.hh>
#include <CommBasicObjects/CommBatteryParameterACE.hh>
#include <CommBasicObjects/CommBatteryState.hh>
#include <CommBasicObjects/CommBatteryStateACE.hh>
#include <CommBasicObjects/CommMobileLaserScan.hh>
#include <CommBasicObjects/CommMobileLaserScanACE.hh>
#include <CommBasicObjects/CommNavigationVelocity.hh>
#include <CommBasicObjects/CommNavigationVelocityACE.hh>
#include <CommBasicObjects/CommVoid.hh>
#include <CommBasicObjects/CommVoidACE.hh>

// include tasks
#include "BatteryEventTask.hh"
#include "PlayerTask.hh"
// include UpcallManagers
#include "LocalizationUpdateServiceInUpcallManager.hh"
#include "NavigationVelocityServiceInUpcallManager.hh"

// include input-handler
#include "LocalizationUpdateHandler.hh"
#include "NavigationVelocityHandler.hh"
// include input-handler
#include "BaseStateQueryHandler.hh"

// include handler
#include "CompHandler.hh"

#include "ParameterStateStruct.hh"
#include "ParameterUpdateHandler.hh"

#include "SmartStateChangeHandler.hh"

#define COMP ComponentPlayerStageSimulator::instance()

class ComponentPlayerStageSimulator : public ComponentPlayerStageSimulatorCore {
private:
	static ComponentPlayerStageSimulator *_componentPlayerStageSimulator;
	
	// constructor
	ComponentPlayerStageSimulator();
	
	// copy-constructor
	ComponentPlayerStageSimulator(const ComponentPlayerStageSimulator& cc);
	
	// destructor
	~ComponentPlayerStageSimulator() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	// helper method that maps a string-name to an according TaskTriggerSubject
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
	// internal map storing the different port-creation factories (that internally map to specific middleware implementations)
	std::map<std::string, ComponentPlayerStageSimulatorPortFactoryInterface*> portFactoryRegistry;
	
	// internal map storing various extensions of this component class
	std::map<std::string, ComponentPlayerStageSimulatorExtension*> componentExtensionRegistry;
	
public:
	ParameterStateStruct getGlobalState() const
	{
		return paramHandler.getGlobalState();
	}
	
	ParameterStateStruct getParameters() const
	{
		return paramHandler.getGlobalState();
	}
	
	// define tasks
	Smart::TaskTriggerSubject* batteryEventTaskTrigger;
	BatteryEventTask *batteryEventTask;
	Smart::TaskTriggerSubject* playerTaskTrigger;
	PlayerTask *playerTask;
	
	// define input-ports
	// InputPort LocalizationUpdateServiceIn
	Smart::ISendServerPattern<CommBasicObjects::CommBasePositionUpdate> *localizationUpdateServiceIn;
	Smart::InputTaskTrigger<CommBasicObjects::CommBasePositionUpdate> *localizationUpdateServiceInInputTaskTrigger;
	LocalizationUpdateServiceInUpcallManager *localizationUpdateServiceInUpcallManager;
	// InputPort NavigationVelocityServiceIn
	Smart::ISendServerPattern<CommBasicObjects::CommNavigationVelocity> *navigationVelocityServiceIn;
	Smart::InputTaskTrigger<CommBasicObjects::CommNavigationVelocity> *navigationVelocityServiceInInputTaskTrigger;
	NavigationVelocityServiceInUpcallManager *navigationVelocityServiceInUpcallManager;
	
	// define request-ports
	
	// define input-handler
	LocalizationUpdateHandler *localizationUpdateHandler;
	NavigationVelocityHandler *navigationVelocityHandler;
	
	// define output-ports
	Smart::IPushServerPattern<CommBasicObjects::CommBaseState> *baseStateServiceOut;
	Smart::IEventServerPattern<CommBasicObjects::CommBatteryParameter, CommBasicObjects::CommBatteryEvent, CommBasicObjects::CommBatteryState,SmartACE::EventId> *batteryEventServiceOut;
	Smart::IEventTestHandler<CommBasicObjects::CommBatteryParameter, CommBasicObjects::CommBatteryEvent, CommBasicObjects::CommBatteryState> *batteryEventServiceOutEventTestHandler; 
	Smart::IPushServerPattern<CommBasicObjects::CommMobileLaserScan> *laserServiceOut;
	
	// define answer-ports
	Smart::IQueryServerPattern<CommBasicObjects::CommVoid, CommBasicObjects::CommBaseState,SmartACE::QueryId> *baseStateAnswerer;
	Smart::QueryServerTaskTrigger<CommBasicObjects::CommVoid, CommBasicObjects::CommBaseState,SmartACE::QueryId> *baseStateAnswererInputTaskTrigger;
	
	// define request-handlers
	BaseStateQueryHandler *baseStateQueryHandler;
	
	// definitions of ComponentPlayerStageSimulatorROSExtension
	
	// definitions of PlainOpcUaComponentPlayerStageSimulatorExtension
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	ParamUpdateHandler paramHandler;
	SmartACE::ParameterSlave *param;
	
	
	/// this method is used to register different PortFactory classes (one for each supported middleware framework)
	void addPortFactory(const std::string &name, ComponentPlayerStageSimulatorPortFactoryInterface *portFactory);
	
	SmartACE::SmartComponent* getComponentImpl();
	
	/// this method is used to register different component-extension classes
	void addExtension(ComponentPlayerStageSimulatorExtension *extension);
	
	/// this method allows to access the registered component-extensions (automatically converting to the actuall implementation type)
	template <typename T>
	T* getExtension(const std::string &name) {
		auto it = componentExtensionRegistry.find(name);
		if(it != componentExtensionRegistry.end()) {
			return dynamic_cast<T*>(it->second);
		}
		return 0;
	}
	
	/// initialize component's internal members
	void init(int argc, char *argv[]);
	
	/// execute the component's infrastructure
	void run();
	
	/// clean-up component's resources
	void fini();
	
	/// call this method to set the overall component into the Alive state (i.e. component is then ready to operate)
	void setStartupFinished();
	
	/// connect all component's client ports
	Smart::StatusCode connectAndStartAllServices();
	
	/// start all assocuated Activities
	void startAllTasks();
	
	/// start all associated timers
	void startAllTimers();
	

	// return singleton instance
	static ComponentPlayerStageSimulator* instance()
	{
		if(_componentPlayerStageSimulator == 0) {
			_componentPlayerStageSimulator = new ComponentPlayerStageSimulator();
		}
		return _componentPlayerStageSimulator;
	}
	
	static void deleteInstance() {
		if(_componentPlayerStageSimulator != 0) {
			delete _componentPlayerStageSimulator;
		}
	}
	
	// connections parameter
	struct connections_struct
	{
		// component struct
		struct component_struct
		{
			// the name of the component
			std::string name;
			std::string initialComponentMode;
			std::string defaultScheduler;
			bool useLogger;
		} component;
		
		//--- task parameter ---
		struct BatteryEventTask_struct {
			double minActFreq;
			double maxActFreq;
			std::string trigger;
			// only one of the following two params is 
			// actually used at run-time according 
			// to the system config model
			double periodicActFreq;
			// or
			std::string inPortRef;
			int prescale;
			// scheduling parameters
			std::string scheduler;
			int priority;
			int cpuAffinity;
		} batteryEventTask;
		struct PlayerTask_struct {
			double minActFreq;
			double maxActFreq;
			std::string trigger;
			// only one of the following two params is 
			// actually used at run-time according 
			// to the system config model
			double periodicActFreq;
			// or
			std::string inPortRef;
			int prescale;
			// scheduling parameters
			std::string scheduler;
			int priority;
			int cpuAffinity;
		} playerTask;
		
		//--- upcall parameter ---
		struct LocalizationUpdateHandler_struct {
			int prescale;
		} localizationUpdateHandler;
		struct NavigationVelocityHandler_struct {
			int prescale;
		} navigationVelocityHandler;
		
		//--- server port parameter ---
		struct BaseStateAnswerer_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} baseStateAnswerer;
		struct BaseStateServiceOut_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} baseStateServiceOut;
		struct BatteryEventServiceOut_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} batteryEventServiceOut;
		struct LaserServiceOut_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} laserServiceOut;
		struct LocalizationUpdateServiceIn_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} localizationUpdateServiceIn;
		struct NavigationVelocityServiceIn_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} navigationVelocityServiceIn;
	
		//--- client port parameter ---
		
		// -- parameters for ComponentPlayerStageSimulatorROSExtension
		
		// -- parameters for PlainOpcUaComponentPlayerStageSimulatorExtension
		
	} connections;
};
#endif
