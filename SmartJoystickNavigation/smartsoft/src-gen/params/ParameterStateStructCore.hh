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
#ifndef _PARAMETERSTATESTRUCTCORE_HH
#define _PARAMETERSTATESTRUCTCORE_HH

#include "aceSmartSoft.hh"

#include <iostream>

// forward declaration (in order to define validateCOMMIT(ParameterStateStruct) which is implemented in derived class)
class ParameterStateStruct;

class ParameterStateStructCore
{
	friend class ParamUpdateHandler;
public:
	
		///////////////////////////////////////////
		// Internal params
		///////////////////////////////////////////
		
		/**
		 * Definition of Parameter Settings
		 */
		class SettingsType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			double max_steering;
			double max_velocity;
		
		public:
			// default constructor
			SettingsType() {
				max_steering = 1.2;
				max_velocity = 1.0;
			}
		
			/**
			 * here are the public getters
			 */
			inline double getMax_steering() const { return max_steering; }
			inline double getMax_velocity() const { return max_velocity; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "Settings(";
				os << "max_steering = " << max_steering << ", ";
				os << "max_velocity = " << max_velocity << ", ";
				os << ")\n";
			}
			
		}; // end class SettingsType
		
	
		///////////////////////////////////////////
		// External params
		///////////////////////////////////////////
		
	
		///////////////////////////////////////////
		// Instance params
		///////////////////////////////////////////
		
	
protected:

	// Internal params
	SettingsType Settings;
	
	// External params
	
	// Instance params (encapsulated in a wrapper class for each instantiated parameter repository)
	

	void setContent(const ParameterStateStructCore &commit) {
		// External params
	
	}

	// special trigger method (user upcall) called before updating parameter global state
	virtual SmartACE::ParamResponseType handleCOMMIT(const ParameterStateStruct &commitState) = 0;
public:
	ParameterStateStructCore() {  }
	virtual ~ParameterStateStructCore() {  }
	
	// internal param getters
	SettingsType getSettings() const {
		return Settings;
	}
	
	// external param getters
	
	// repo wrapper class getter(s)
	
	// helper method to easily implement output stream in derived classes
	void to_ostream(std::ostream &os = std::cout) const
	{
		// Internal params
		Settings.to_ostream(os);
		
		// External params
		
		// Instance params (encapsulated in a wrapper class for each instantiated parameter repository)
	}
};

#endif
