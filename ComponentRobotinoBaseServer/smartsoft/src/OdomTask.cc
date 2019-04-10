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
//--------------------------------------------------------------------------
//
//  Copyright (C) 2012 Matthias Hörger
//
//        schlegel@hs-ulm.de
//        steck@hs-ulm.de
//
//        ZAFH Servicerobotic Ulm
//        University of Applied Sciences
//        Prittwitzstr. 10
//        89075 Ulm
//        Germany
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//--------------------------------------------------------------------------
#include "OdomTask.hh"
#include <iostream>
#include "ComponentRobotinoBaseServer.hh"

OdomTask::OdomTask(SmartACE::SmartComponent *comp) 
:	OdomTaskCore(comp)
{
	std::cout << "constructor OdomTask\n";
}
OdomTask::~OdomTask() 
{
	std::cout << "destructor OdomTask\n";
}



int OdomTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	return 0;
}
int OdomTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	time_stamp.set_now(); // Set the timestamp to the current time

	//base_velocity.set_v((xSpeed + ySpeed) / 2);
//	base_velocity.set_vX(COMP->robot->getVx(),1);
//	base_velocity.set_vY(COMP->robot->getVy(),1);
//	//base_velocity.set_omega_base(yawSpeed);
//	base_velocity.set_WZ_base(COMP->robot->getOmegaRad());

	base_velocity = COMP->robot->getBaseVelocity();

	//std::cout<<"BaseStateHandler - vel: "<<base_velocity<<std::endl;

	// push the objects CommBasePosition and CommBaseVelocity into the SmartSoft CommBaseState object
	base_state.set_time_stamp(time_stamp);
	//    base_state.set_base_position(base_position);
	base_state.set_base_position(COMP->robot->getBasePosition());
	base_state.set_base_raw_position(COMP->robot->getBaseRawPosition());
	base_state.set_base_velocity(base_velocity);

        CommBasicObjects::CommBatteryLevel batteryLevel;
        batteryLevel.setPotential(COMP->robot->getBatteryVoltage());

        batteryLevel.setCurrent(COMP->robot->getBatteryCurrent());
        batteryLevel.setExternalPower(COMP->robot->getExternalPower());

	base_state.set_battery_state(batteryLevel);

	if(COMP->getGlobalState().getGeneral().getVerbose() == true)
	{
		std::cout<<"Base Pose: "<<base_state.getBasePose().get_base_pose3d().get_position()<<std::endl;
		std::cout<<"RobotinoExternaPower: "<<COMP->robot->getExternalPower()<<std::endl;
	}

	// send the CommBaseState object to the client
	const Smart::StatusCode status = COMP->baseStateServiceOut->put(base_state);
	if ( status != Smart::SMART_OK )
	{
		std::cerr << "ERROR: failed to push base state ("
				<< Smart::StatusCodeConversion(status) << ")" << std::endl;
	}

	CommBasicObjects::CommBatteryState batteryState;
	batteryState.setChargeValue(COMP->robot->getBatteryVoltage());
	COMP->batteryEventServiceOut->put(batteryState);


	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int OdomTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
