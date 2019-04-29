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
#ifndef _WATCHDOGTASK_HH
#define _WATCHDOGTASK_HH

#include "WatchDogTaskCore.hh"

class WatchDogTask  : public WatchDogTaskCore
{
private:
	static bool _running;
	static unsigned int _count;
	static unsigned int _lastCount;
public:
	WatchDogTask(SmartACE::SmartComponent *comp);
	virtual ~WatchDogTask();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();

	static void watchDogStart();
    static void watchDogReset();
};

#endif