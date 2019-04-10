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
#ifndef _SMARTPLANNERBREADTHFIRSTSEARCH_HH
#define _SMARTPLANNERBREADTHFIRSTSEARCH_HH

#include <map>
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "SmartPlannerBreadthFirstSearchCore.hh"

#include "SmartPlannerBreadthFirstSearchPortFactoryInterface.hh"
#include "SmartPlannerBreadthFirstSearchExtension.hh"

// forward declarations
class SmartPlannerBreadthFirstSearchPortFactoryInterface;
class SmartPlannerBreadthFirstSearchExtension;

// includes for SmartPlannerBreadthFirstSearchROSExtension

// includes for PlainOpcUaSmartPlannerBreadthFirstSearchExtension
// include plain OPC UA device clients
// include plain OPC UA status servers


// include communication objects
#include <CommBasicObjects/CommBaseState.hh>
#include <CommBasicObjects/CommBaseStateACE.hh>
#include <CommNavigationObjects/CommGridMap.hh>
#include <CommNavigationObjects/CommGridMapACE.hh>
#include <CommNavigationObjects/CommPlannerEventParameter.hh>
#include <CommNavigationObjects/CommPlannerEventParameterACE.hh>
#include <CommNavigationObjects/CommPlannerEventResult.hh>
#include <CommNavigationObjects/CommPlannerEventResultACE.hh>
#include <CommNavigationObjects/CommPlannerGoal.hh>
#include <CommNavigationObjects/CommPlannerGoalACE.hh>
#include <CommNavigationObjects/PlannerEventState.hh>
#include <CommNavigationObjects/PlannerEventStateACE.hh>

// include tasks
#include "PlannerTask.hh"
// include UpcallManagers
#include "BaseStateClientUpcallManager.hh"
#include "CurMapClientUpcallManager.hh"

// include input-handler
// include input-handler

// include handler
#include "CompHandler.hh"

#include "ParameterStateStruct.hh"
#include "ParameterUpdateHandler.hh"

#include "SmartStateChangeHandler.hh"

#define COMP SmartPlannerBreadthFirstSearch::instance()

class SmartPlannerBreadthFirstSearch : public SmartPlannerBreadthFirstSearchCore {
private:
	static SmartPlannerBreadthFirstSearch *_smartPlannerBreadthFirstSearch;
	
	// constructor
	SmartPlannerBreadthFirstSearch();
	
	// copy-constructor
	SmartPlannerBreadthFirstSearch(const SmartPlannerBreadthFirstSearch& cc);
	
	// destructor
	~SmartPlannerBreadthFirstSearch() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	// helper method that maps a string-name to an according TaskTriggerSubject
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
	// internal map storing the different port-creation factories (that internally map to specific middleware implementations)
	std::map<std::string, SmartPlannerBreadthFirstSearchPortFactoryInterface*> portFactoryRegistry;
	
	// internal map storing various extensions of this component class
	std::map<std::string, SmartPlannerBreadthFirstSearchExtension*> componentExtensionRegistry;
	
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
	Smart::TaskTriggerSubject* plannerTaskTrigger;
	PlannerTask *plannerTask;
	
	// define input-ports
	// InputPort BaseStateClient
	Smart::IPushClientPattern<CommBasicObjects::CommBaseState> *baseStateClient;
	Smart::InputTaskTrigger<CommBasicObjects::CommBaseState> *baseStateClientInputTaskTrigger;
	BaseStateClientUpcallManager *baseStateClientUpcallManager;
	// InputPort CurMapClient
	Smart::IPushClientPattern<CommNavigationObjects::CommGridMap> *curMapClient;
	Smart::InputTaskTrigger<CommNavigationObjects::CommGridMap> *curMapClientInputTaskTrigger;
	CurMapClientUpcallManager *curMapClientUpcallManager;
	
	// define request-ports
	
	// define input-handler
	
	// define output-ports
	Smart::IEventServerPattern<CommNavigationObjects::CommPlannerEventParameter, CommNavigationObjects::CommPlannerEventResult, CommNavigationObjects::PlannerEventState,SmartACE::EventId> *plannerEventServer;
	Smart::IEventTestHandler<CommNavigationObjects::CommPlannerEventParameter, CommNavigationObjects::CommPlannerEventResult, CommNavigationObjects::PlannerEventState> *plannerEventServerEventTestHandler; 
	Smart::IPushServerPattern<CommNavigationObjects::CommPlannerGoal> *plannerGoalServer;
	
	// define answer-ports
	
	// define request-handlers
	
	// definitions of SmartPlannerBreadthFirstSearchROSExtension
	
	// definitions of PlainOpcUaSmartPlannerBreadthFirstSearchExtension
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	ParamUpdateHandler paramHandler;
	SmartACE::ParameterSlave *param;
	
	
	/// this method is used to register different PortFactory classes (one for each supported middleware framework)
	void addPortFactory(const std::string &name, SmartPlannerBreadthFirstSearchPortFactoryInterface *portFactory);
	
	SmartACE::SmartComponent* getComponentImpl();
	
	/// this method is used to register different component-extension classes
	void addExtension(SmartPlannerBreadthFirstSearchExtension *extension);
	
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
	
	Smart::StatusCode connectBaseStateClient(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectCurMapClient(const std::string &serverName, const std::string &serviceName);

	// return singleton instance
	static SmartPlannerBreadthFirstSearch* instance()
	{
		if(_smartPlannerBreadthFirstSearch == 0) {
			_smartPlannerBreadthFirstSearch = new SmartPlannerBreadthFirstSearch();
		}
		return _smartPlannerBreadthFirstSearch;
	}
	
	static void deleteInstance() {
		if(_smartPlannerBreadthFirstSearch != 0) {
			delete _smartPlannerBreadthFirstSearch;
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
		struct PlannerTask_struct {
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
		} plannerTask;
		
		//--- upcall parameter ---
		
		//--- server port parameter ---
		struct PlannerEventServer_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} plannerEventServer;
		struct PlannerGoalServer_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} plannerGoalServer;
	
		//--- client port parameter ---
		struct BaseStateClient_struct {
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} baseStateClient;
		struct CurMapClient_struct {
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} curMapClient;
		
		// -- parameters for SmartPlannerBreadthFirstSearchROSExtension
		
		// -- parameters for PlainOpcUaSmartPlannerBreadthFirstSearchExtension
		
	} connections;
};
#endif
