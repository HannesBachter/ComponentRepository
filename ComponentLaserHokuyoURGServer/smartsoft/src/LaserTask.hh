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
//------------------------------------------------------------------------
//
//  Copyright (C) 2010 Manuel Wopfner
//
//        wopfner@hs-ulm.de
//
//        Christian Schlegel (schlegel@hs-ulm.de)
//        University of Applied Sciences
//        Prittwitzstr. 10
//        89075 Ulm (Germany)
//
//  This file is part of the "SmartLaserHokuyoURGServer2 component".
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
//--------------------------------------------------------------------------
#ifndef _LASERTASK_HH
#define _LASERTASK_HH

#include "LaserTaskCore.hh"
#include "hokuyo/HokuyoDriver.h"
#include "ParameterStateStruct.hh"

#include <armadillo.hh>
#include "CommBasicObjects/CommMobileLaserScan.hh"
#include "CommBasicObjects/CommBaseState.hh"
#include "CommManipulatorObjects/CommManipulatorState.hh"
#include "CommManipulatorObjects/CommMobileManipulatorState.hh"


class myLaser :public HokuyoDriver{

	std::list<hokuyo::LaserScan> scanList;
	SmartACE::SmartMutex scanListLock;
	SmartACE::SmartSemaphore scanSema;

	virtual void hokuyoScanCallback( const hokuyo::LaserScan& scan ){
		SmartACE::SmartGuard g(scanListLock);
		   this->scanList.push_back(scan);
		   scanSema.release();
	}

public:
	myLaser():scanSema(0){
	}

	hokuyo::LaserScan getNextScan(){
		scanSema.acquire();
		SmartACE::SmartGuard g(scanListLock);
		hokuyo::LaserScan scan = this->scanList.front();
		this->scanList.pop_front();
		return scan;
	}
};

class LaserTask  : public LaserTaskCore
{
public:
	LaserTask(SmartACE::SmartComponent *comp);
	virtual ~LaserTask();

	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();
	bool accquireNewScan(CommBasicObjects::CommMobileLaserScan& scan, ParameterStateStruct& localstate);

	void startScanner(){
		laser.doStart();
	}
	void stopScanner(){
		laser.doStop();
	}
private:
	ulong scan_id;
	myLaser laser;


	CommBasicObjects::CommBasePose _default_base_position;

	// position of scanner on robot
	double _scanner_x;
	double _scanner_y;
	double _scanner_z;
	double _scanner_a; // azimuth relative to coordinate system of mounting point

	CommBasicObjects::CommMobileLaserScan scan;
	CommBasicObjects::CommBaseState base_state;
	CommManipulatorObjects::CommManipulatorState manipulator_state;
	CommManipulatorObjects::CommMobileManipulatorState mobile_manipulator_state;

	CommBasicObjects::CommBaseVelocity zero_velocity;

	bool openLaser();
};

#endif
