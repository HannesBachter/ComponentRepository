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

#ifndef COMPONENTUNICAPIMAGESERVER_OPC_UA_BACKEND_PORTFACTORY_HH_
#define COMPONENTUNICAPIMAGESERVER_OPC_UA_BACKEND_PORTFACTORY_HH_

// include the main component-definition class
#include "ComponentUnicapImageServerPortFactoryInterface.hh"

#include <thread>
#include <chrono>

// include SeRoNetSDK library
#include <SeRoNetSDK/SeRoNet/Utils/Task.hpp>
#include <SeRoNetSDK/SeRoNet/Utils/Component.hpp>

class ComponentUnicapImageServerOpcUaBackendPortFactory: public ComponentUnicapImageServerPortFactoryInterface
{
private:
	// internal component instance
	SeRoNet::Utils::Component *componentImpl;
	
	// component thread
	std::thread component_thread;
	
	// internal component thread method
	int task_execution();
public:
	ComponentUnicapImageServerOpcUaBackendPortFactory();
	virtual ~ComponentUnicapImageServerOpcUaBackendPortFactory();

	virtual void initialize(ComponentUnicapImageServer *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	virtual Smart::IPushClientPattern<CommBasicObjects::CommBaseState> * createBasePushTimedClient() override;
	virtual Smart::IPushClientPattern<CommBasicObjects::CommDevicePoseState> * createPtuPushTimedClient() override;
	
	virtual Smart::IPushServerPattern<DomainVision::CommVideoImage> * createImagePushNewestServer(const std::string &serviceName) override;
	virtual Smart::IQueryServerPattern<CommBasicObjects::CommVoid, DomainVision::CommVideoImage> * createImageQueryServer(const std::string &serviceName) override;
	
	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* COMPONENTUNICAPIMAGESERVER_SERONET_SDK_PORTFACTORY_HH_ */