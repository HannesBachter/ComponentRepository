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
#include "ComponentTrafficLightTest.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "ComponentTrafficLightTestAcePortFactory.hh"


// initialize static singleton pointer to zero
ComponentTrafficLightTest* ComponentTrafficLightTest::_componentTrafficLightTest = 0;

// constructor
ComponentTrafficLightTest::ComponentTrafficLightTest()
{
	std::cout << "constructor of ComponentTrafficLightTest\n";
	
	// set all pointer members to NULL
	generateOut = NULL;
	generateOutTrigger = NULL;
	trafficLightServiceOut = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	
	// set default ini parameter values
	connections.component.name = "ComponentTrafficLightTest";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.trafficLightServiceOut.initialConnect = false;
	connections.trafficLightServiceOut.wiringName = "TrafficLightServiceOut";
	connections.trafficLightServiceOut.serverName = "unknown";
	connections.trafficLightServiceOut.serviceName = "unknown";
	connections.trafficLightServiceOut.interval = 1;
	connections.trafficLightServiceOut.roboticMiddleware = "ACE_SmartSoft";
	connections.generateOut.minActFreq = 0.0;
	connections.generateOut.maxActFreq = 0.0;
	connections.generateOut.trigger = "PeriodicTimer";
	connections.generateOut.periodicActFreq = 1.0;
	// scheduling default parameters
	connections.generateOut.scheduler = "DEFAULT";
	connections.generateOut.priority = -1;
	connections.generateOut.cpuAffinity = -1;
	
	// initialize members of ComponentTrafficLightTestROSExtension
	
	// initialize members of PlainOpcUaComponentTrafficLightTestExtension
	
}

void ComponentTrafficLightTest::addPortFactory(const std::string &name, ComponentTrafficLightTestPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void ComponentTrafficLightTest::addExtension(ComponentTrafficLightTestExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

SmartACE::SmartComponent* ComponentTrafficLightTest::getComponentImpl()
{
	return dynamic_cast<ComponentTrafficLightTestAcePortFactory*>(portFactoryRegistry["ACE_SmartSoft"])->getComponentImpl();
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void ComponentTrafficLightTest::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}


Smart::StatusCode ComponentTrafficLightTest::connectTrafficLightServiceOut(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.trafficLightServiceOut.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = trafficLightServiceOut->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->trafficLightServiceOut->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	return status;
}


/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode ComponentTrafficLightTest::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	status = connectTrafficLightServiceOut(connections.trafficLightServiceOut.serverName, connections.trafficLightServiceOut.serviceName);
	if(status != Smart::SMART_OK) return status;
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void ComponentTrafficLightTest::startAllTasks() {
	// start task GenerateOut
	if(connections.generateOut.scheduler != "DEFAULT") {
		ACE_Sched_Params generateOut_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.generateOut.scheduler == "FIFO") {
			generateOut_SchedParams.policy(ACE_SCHED_FIFO);
			generateOut_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.generateOut.scheduler == "RR") {
			generateOut_SchedParams.policy(ACE_SCHED_RR);
			generateOut_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		generateOut->start(generateOut_SchedParams, connections.generateOut.cpuAffinity);
	} else {
		generateOut->start();
	}
}

/**
 * Start all timers contained in this component
 */
void ComponentTrafficLightTest::startAllTimers() {
}


Smart::TaskTriggerSubject* ComponentTrafficLightTest::getInputTaskTriggerFromString(const std::string &client)
{
	
	return NULL;
}


void ComponentTrafficLightTest::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		
		// initializations of ComponentTrafficLightTestROSExtension
		
		// initializations of PlainOpcUaComponentTrafficLightTestExtension
		
		
		// initialize all registered port-factories
		for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
		{
			portFactory->second->initialize(this, argc, argv);
		}
		
		// initialize all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->initialize(this, argc, argv);
		}
		
		ComponentTrafficLightTestPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<ComponentTrafficLightTestAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition ComponentTrafficLightTest is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		
		// create client ports
		trafficLightServiceOut = portFactoryRegistry[connections.trafficLightServiceOut.roboticMiddleware]->createTrafficLightServiceOut();
		
		// create InputTaskTriggers and UpcallManagers
		
		// create input-handler
		
		// create request-handlers
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		status = stateSlave->setUpInitialState(connections.component.initialComponentMode);
		if (status != Smart::SMART_OK) std::cerr << status << "; failed setting initial ComponentMode: " << connections.component.initialComponentMode << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		if(connections.trafficLightServiceOut.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::SendClient<DomainHMI::CommTrafficLight>*>(trafficLightServiceOut)->add(wiringSlave, connections.trafficLightServiceOut.wiringName);
		}
		
		
		
		// create Task GenerateOut
		generateOut = new GenerateOut(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		if(connections.generateOut.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.generateOut.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(generateOut);
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				generateOutTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task GenerateOut" << std::endl;
			}
		} else if(connections.generateOut.trigger == "DataTriggered") {
			generateOutTrigger = getInputTaskTriggerFromString(connections.generateOut.inPortRef);
			if(generateOutTrigger != NULL) {
				generateOutTrigger->attach(generateOut, connections.generateOut.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.generateOut.inPortRef << " as activation source for Task GenerateOut" << std::endl;
			}
		} else
		{
			// setup default task-trigger as PeriodicTimer
			Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
			int microseconds = 1000*1000 / 1.0;
			if(microseconds > 0) {
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				triggerPtr->attach(generateOut);
				// store trigger in class member
				generateOutTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task GenerateOut" << std::endl;
			}
		}
		
		
		// link observers with subjects
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std exception" << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}

// run the component
void ComponentTrafficLightTest::run()
{
	stateSlave->acquire("init");
	// startup all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onStartup();
	}
	
	// startup all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onStartup();
	}
	stateSlave->release("init");
	
	// do not call this handler within the init state (see above) as this handler internally calls setStartupFinished() (this should be fixed in future)
	compHandler.onStartup();
	
	// this call blocks until the component is commanded to shutdown
	stateSlave->acquire("shutdown");
	
	// shutdown all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onShutdown();
	}
	
	// shutdown all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onShutdown();
	}
	
	if(connections.component.useLogger == true) {
		//FIXME: use logging
		//Smart::LOGGER->stopLogging();
	}
	
	compHandler.onShutdown();
	
	stateSlave->release("shutdown");
}

// clean-up component's resources
void ComponentTrafficLightTest::fini()
{
	// unlink all observers
	
	// destroy all task instances
	// unlink all UpcallManagers
	// unlink the TaskTrigger
	if(generateOutTrigger != NULL){
		generateOutTrigger->detach(generateOut);
		delete generateOut;
	}

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers

	// destroy client ports
	delete trafficLightServiceOut;

	// destroy server ports
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	
	delete stateSlave;
	// destroy state-change-handler
	delete stateChangeHandler;
	
	// destroy all master/slave ports
	delete wiringSlave;
	

	// destroy all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->destroy();
	}

	// destroy all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->destroy();
	}
	
	// destruction of ComponentTrafficLightTestROSExtension
	
	// destruction of PlainOpcUaComponentTrafficLightTestExtension
	
}

void ComponentTrafficLightTest::loadParameter(int argc, char *argv[])
{
	/*
	 Parameters can be specified via command line --filename=<filename> or -f <filename>

	 With this parameter present:
	   - The component will look for the file in the current working directory,
	     a path relative to the current directory or any absolute path
	   - The component will use the default values if the file cannot be found

	 With this parameter absent:
	   - <Name of Component>.ini will be read from current working directory, if found there
	   - $SMART_ROOT/etc/<Name of Component>.ini will be read otherwise
	   - Default values will be used if neither found in working directory or /etc
	 */
	SmartACE::SmartIniParameter parameter;
	std::ifstream parameterfile;
	bool parameterFileFound = false;

	// load parameters
	try
	{
		// if paramfile is given as argument
		if(parameter.tryAddFileFromArgs(argc,argv,"filename", 'f'))
		{
			parameterFileFound = true;
			std::cout << "parameter file is loaded from an argv argument \n";
		} else if(parameter.searchFile("ComponentTrafficLightTest.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load ComponentTrafficLightTest.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: ComponentTrafficLightTest.ini parameter file not found! (using default values or command line arguments)\n";
		}
		
		// add command line arguments to allow overwriting of parameters
		// from file
		parameter.addCommandLineArgs(argc,argv,"component");
		
		// initialize the naming service using the command line parameters parsed in the
		// SmartIniParameter class. The naming service parameters are expected to be in
		// the "component" parameter group.
		SmartACE::NAMING::instance()->checkForHelpArg(argc,argv);
		if(parameterFileFound) 
		{
			if(SmartACE::NAMING::instance()->init(parameter.getAllParametersFromGroup("component")) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		} else {
			if(SmartACE::NAMING::instance()->init(argc, argv) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		}
			
		// print all known parameters
		// parameter.print();
		
		//--- server port // client port // other parameter ---
		// load parameter
		parameter.getString("component", "name", connections.component.name);
		parameter.getString("component", "initialComponentMode", connections.component.initialComponentMode);
		if(parameter.checkIfParameterExists("component", "defaultScheduler")) {
			parameter.getString("component", "defaultScheduler", connections.component.defaultScheduler);
		}
		if(parameter.checkIfParameterExists("component", "useLogger")) {
			parameter.getBoolean("component", "useLogger", connections.component.useLogger);
		}
		
		// load parameters for client TrafficLightServiceOut
		parameter.getBoolean("TrafficLightServiceOut", "initialConnect", connections.trafficLightServiceOut.initialConnect);
		parameter.getString("TrafficLightServiceOut", "serviceName", connections.trafficLightServiceOut.serviceName);
		parameter.getString("TrafficLightServiceOut", "serverName", connections.trafficLightServiceOut.serverName);
		parameter.getString("TrafficLightServiceOut", "wiringName", connections.trafficLightServiceOut.wiringName);
		if(parameter.checkIfParameterExists("TrafficLightServiceOut", "roboticMiddleware")) {
			parameter.getString("TrafficLightServiceOut", "roboticMiddleware", connections.trafficLightServiceOut.roboticMiddleware);
		}
		
		
		// load parameters for task GenerateOut
		parameter.getDouble("GenerateOut", "minActFreqHz", connections.generateOut.minActFreq);
		parameter.getDouble("GenerateOut", "maxActFreqHz", connections.generateOut.maxActFreq);
		parameter.getString("GenerateOut", "triggerType", connections.generateOut.trigger);
		if(connections.generateOut.trigger == "PeriodicTimer") {
			parameter.getDouble("GenerateOut", "periodicActFreqHz", connections.generateOut.periodicActFreq);
		} else if(connections.generateOut.trigger == "DataTriggered") {
			parameter.getString("GenerateOut", "inPortRef", connections.generateOut.inPortRef);
			parameter.getInteger("GenerateOut", "prescale", connections.generateOut.prescale);
		}
		if(parameter.checkIfParameterExists("GenerateOut", "scheduler")) {
			parameter.getString("GenerateOut", "scheduler", connections.generateOut.scheduler);
		}
		if(parameter.checkIfParameterExists("GenerateOut", "priority")) {
			parameter.getInteger("GenerateOut", "priority", connections.generateOut.priority);
		}
		if(parameter.checkIfParameterExists("GenerateOut", "cpuAffinity")) {
			parameter.getInteger("GenerateOut", "cpuAffinity", connections.generateOut.cpuAffinity);
		}
		
		// load parameters for ComponentTrafficLightTestROSExtension
		
		// load parameters for PlainOpcUaComponentTrafficLightTestExtension
		
		
		// load parameters for all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->loadParameters(parameter);
		}
		
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}
