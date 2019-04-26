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
#ifndef _COMPONENTVISUALIZATIONCORE_HH
#define _COMPONENTVISUALIZATIONCORE_HH
	
#include "aceSmartSoft.hh"
#include <iostream>
#include <mrpt/gui.h>
#include <mrpt/opengl.h>

using namespace mrpt;
using namespace mrpt::math;
using namespace mrpt::gui;

class ComponentVisualizationCore
{
private:
	CDisplayWindow3D *window3D;

public:
	CDisplayWindow3D& getWindow3d() {
			return *window3D;
		}
	ComponentVisualizationCore();
	~ComponentVisualizationCore();
};
	
#endif
