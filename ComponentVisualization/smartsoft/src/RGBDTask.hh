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
#ifndef _RGBDTASK_HH
#define _RGBDTASK_HH

#include "RGBDTaskCore.hh"
#include "visualization/RGBDVisualization.hh"
#include "DomainVision/CommRGBDImage.hh"
class RGBDTask  : public RGBDTaskCore
{
private:
	RGBDVisualization* rgbd_viz;
	DomainVision::CommRGBDImage image;
public:
	RGBDTask(SmartACE::SmartComponent *comp);
	virtual ~RGBDTask();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();
};

#endif
