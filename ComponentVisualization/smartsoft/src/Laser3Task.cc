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

// --------------------------------------------------------------------------
//
//  Copyright (C) 2011 Manuel Wopfner
//
//        schlegel@hs-ulm.de
//
//        ZAFH Servicerobotik Ulm
//        University of Applied Sciences
//        Prittwitzstr. 10
//        D-89075 Ulm
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
// --------------------------------------------------------------------------


#include "Laser3Task.hh"
#include "ComponentVisualization.hh"

#include <iostream>

Laser3Task::Laser3Task(SmartACE::SmartComponent *comp) 
:	Laser3TaskCore(comp)
{
	std::cout << "constructor Laser3Task\n";
}
Laser3Task::~Laser3Task() 
{
	std::cout << "destructor Laser3Task\n";
}

int Laser3Task::connectServices(){
	std::cout << "connecting to: " << COMP->connections.laserClient3.serverName << "; " << COMP->connections.laserClient3.serviceName << std::endl;
	Smart::StatusCode status = COMP->laserClient3->connect(COMP->connections.laserClient3.serverName, COMP->connections.laserClient3.serviceName);
	while (status != Smart::SMART_OK) {
		usleep(500000);
		status = COMP->laserClient3->connect(COMP->connections.laserClient3.serverName, COMP->connections.laserClient3.serviceName);
	}
	std::cout << COMP->connections.laserClient3.serverName << "; " << COMP->connections.laserClient3.serviceName << " connected.\n";
	return 0;
}
int Laser3Task::disconnectServices(){
	COMP->laserClient3->disconnect();
	return 0;
}

int Laser3Task::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	laser = new LaserVisualization(COMP->getWindow3d(), "Laser3");

	COMP->laserClient3->subscribe();

	return (laser!=0)?0:1;
}
int Laser3Task::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel

	Smart::StatusCode status = COMP->laserClient3->getUpdateWait(scan);
	if (status == Smart::SMART_OK) {
		laser->displayLaserScan(scan);
	} else {
		laser->clear();
	}

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int Laser3Task::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	delete laser;
	COMP->laserClient3->unsubscribe();
	return 0;
}
