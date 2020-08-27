//--------------------------------------------------------------------------
// This file is generated by the SeRoNet Tooling. The SeRoNet Tooling is 
// developed by the SeRoNet Project consortium: 
// http://www.seronet-projekt.de
//
// The ROS Mixed-Port Component is developed by:
// Service Robotics Research Center of Ulm University of Applied Sciences
// Fraunhofer Institute for Manufacturing Engineering and Automation IPA
//
// This code-generator uses infrastructure of the SmartMDSD Toolchain on
// which the SeRoNet Tooling is based on.
//
// CAUTION: 
// This software is a preview for the purpose of technology demonstration. 
// It is experimental and comes with no support. Use at your own risk.
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------

#ifndef ROS_PORT_COMPONENT_EXTENSION_H_
#define ROS_PORT_COMPONENT_EXTENSION_H_

#include "ComponentRosBaseFakeRosPortBaseClass.hh"
#include "ComponentRosBaseFakeRosPortCallbacks.hh"

#include "ComponentRosBaseFakeExtension.hh"

// include component's main class
#include "ComponentRosBaseFake.hh"

class ComponentRosBaseFakeRosPortExtension : public ComponentRosBaseFakeExtension, public ComponentRosBaseFakeRosPortBaseClass
{
private:
	ros::NodeHandle *nh;
	
	ComponentRosBaseFakeRosPortCallbacks *callbacksPtr;
	
	virtual int extensionExecution() override;
public:
	ComponentRosBaseFakeRosPortExtension();
	virtual ~ComponentRosBaseFakeRosPortExtension();

	virtual void loadParameters(const SmartACE::SmartIniParameter &parameter);
	virtual void initialize(ComponentRosBaseFake *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	inline ros::Publisher* getTwist_pubPtr() {
		return &twist_pub;
	}

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* ROS_PORT_COMPONENT_EXTENSION_H_ */