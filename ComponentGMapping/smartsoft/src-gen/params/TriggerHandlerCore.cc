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

#include "TriggerHandlerCore.hh"


//
// trigger internal handler methods
//

	// handle INITNEWMAP
	void TriggerHandlerCore::handleCommLocalizationObjects_SlamParameter_INITNEWMAPCore(const int &x, const int &y, const int &a)
	{
		this->handleCommLocalizationObjects_SlamParameter_INITNEWMAP(x, y, a);
	}

	// handle SAVEMAP
	void TriggerHandlerCore::handleCommLocalizationObjects_SlamParameter_SAVEMAPCore(const std::string &dirname, const std::string &filename)
	{
		this->handleCommLocalizationObjects_SlamParameter_SAVEMAP(dirname, filename);
	}

//
// extended trigger internal handler methods
//
