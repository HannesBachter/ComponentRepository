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
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#include "TwistActivity.hh"
#include "ComponentRosDock.hh"

#include <iostream>

TwistActivity::TwistActivity(SmartACE::SmartComponent *comp) 
:	TwistActivityCore(comp)
{
	std::cout << "constructor TwistActivity\n";
}
TwistActivity::~TwistActivity() 
{
	std::cout << "destructor TwistActivity\n";
}

void TwistActivity::twist_sub_cb(const geometry_msgs::Twist::ConstPtr &msg)
{
    CommBasicObjects::CommNavigationVelocity comNavVel;

    comNavVel.set_vX(msg->linear.x);
    comNavVel.set_vY(msg->linear.y);
	comNavVel.set_omega(msg->angular.z);
//	std::cout << "Velocity x: " << msg->linear.x	<< std::endl;
//	std::cout << "velocity y: " << msg->linear.y	<< std::endl;
//	std::cout << "turnrate :" << msg->angular.z	<< std::endl;

    Smart::StatusCode status_nav;

    status_nav = this->navigationVelocityServiceOutPut(comNavVel);
    if(status_nav != Smart::SMART_OK)
	{
		std::cerr << status_nav << std::endl;
		std::cout << "Some Error in the Conection as status is not ok " << std::endl;
	}
	else
	{
		std::cout << "Updating Velocity " << comNavVel << std::endl;
	}
}

int TwistActivity::on_entry()
{
	std::cout << "entry TwistActivity " << std::endl;

	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	return 0;
}
int TwistActivity::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	// to get the incoming data, use this methods:
	Smart::StatusCode status;

	//std::cout << "Hello from TwistActivity " << std::endl;

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int TwistActivity::on_exit()
{
	std::cout << "exit TwistActivity " << std::endl;

	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
