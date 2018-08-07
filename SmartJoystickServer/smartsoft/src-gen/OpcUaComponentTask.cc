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

#include "OpcUaComponentTask.hh"

#include <SeRoNetSDK/SeRoNet/Utils/Component.hpp>

using namespace OpcUa;

ComponentTask::ComponentTask(Smart::IComponent *comp)
:	SmartACE::Task(comp)
{  
	opcUaComponent = new SeRoNet::Utils::Component(comp->getName());
}

ComponentTask::~ComponentTask()
{ 
	delete opcUaComponent;
}

int ComponentTask::svc(void) {
	opcUaComponent->run();
	return 0;
}
