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
		 * Definition of Parameter settings
		 */
		class settingsType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			bool debug_info;
			std::string device_serial_number;
			bool post_processing;
			bool pushnewest_color_image;
			bool pushnewest_depth_image;
			bool pushnewest_rgbd_image;
			bool undistort_image;
			double valid_image_time;
		
		public:
			// default constructor
			settingsType() {
				debug_info = true;
				device_serial_number = "733512070584";
				post_processing = true;
				pushnewest_color_image = true;
				pushnewest_depth_image = false;
				pushnewest_rgbd_image = true;
				undistort_image = true;
				valid_image_time = 1.0;
			}
		
			/**
			 * here are the public getters
			 */
			inline bool getDebug_info() const { return debug_info; }
			inline std::string getDevice_serial_number() const { return device_serial_number; }
			inline bool getPost_processing() const { return post_processing; }
			inline bool getPushnewest_color_image() const { return pushnewest_color_image; }
			inline bool getPushnewest_depth_image() const { return pushnewest_depth_image; }
			inline bool getPushnewest_rgbd_image() const { return pushnewest_rgbd_image; }
			inline bool getUndistort_image() const { return undistort_image; }
			inline double getValid_image_time() const { return valid_image_time; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "settings(";
				os << "debug_info = " << debug_info << ", ";
				os << "device_serial_number = " << device_serial_number << ", ";
				os << "post_processing = " << post_processing << ", ";
				os << "pushnewest_color_image = " << pushnewest_color_image << ", ";
				os << "pushnewest_depth_image = " << pushnewest_depth_image << ", ";
				os << "pushnewest_rgbd_image = " << pushnewest_rgbd_image << ", ";
				os << "undistort_image = " << undistort_image << ", ";
				os << "valid_image_time = " << valid_image_time << ", ";
				os << ")\n";
			}
			
		}; // end class settingsType
		
		/**
		 * Definition of Parameter stereo
		 */
		class stereoType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			float baseline;
		
		public:
			// default constructor
			stereoType() {
				baseline = 49.7852;
			}
		
			/**
			 * here are the public getters
			 */
			inline float getBaseline() const { return baseline; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "stereo(";
				os << "baseline = " << baseline << ", ";
				os << ")\n";
			}
			
		}; // end class stereoType
		
		/**
		 * Definition of Parameter sensor_pose
		 */
		class sensor_poseType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			double azimuth;
			double elevation;
			double roll;
			double x;
			double y;
			double z;
		
		public:
			// default constructor
			sensor_poseType() {
				azimuth = 1.5707963;
				elevation = 3.14159265;
				roll = 1.32;
				x = 90;
				y = 0;
				z = 350;
			}
		
			/**
			 * here are the public getters
			 */
			inline double getAzimuth() const { return azimuth; }
			inline double getElevation() const { return elevation; }
			inline double getRoll() const { return roll; }
			inline double getX() const { return x; }
			inline double getY() const { return y; }
			inline double getZ() const { return z; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "sensor_pose(";
				os << "azimuth = " << azimuth << ", ";
				os << "elevation = " << elevation << ", ";
				os << "roll = " << roll << ", ";
				os << "x = " << x << ", ";
				os << "y = " << y << ", ";
				os << "z = " << z << ", ";
				os << ")\n";
			}
			
		}; // end class sensor_poseType
		
		/**
		 * Definition of Parameter RGB_config
		 */
		class RGB_configType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			int framerate;
			int height;
			int width;
		
		public:
			// default constructor
			RGB_configType() {
				framerate = 30;
				height = 480;
				width = 640;
			}
		
			/**
			 * here are the public getters
			 */
			inline int getFramerate() const { return framerate; }
			inline int getHeight() const { return height; }
			inline int getWidth() const { return width; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "RGB_config(";
				os << "framerate = " << framerate << ", ";
				os << "height = " << height << ", ";
				os << "width = " << width << ", ";
				os << ")\n";
			}
			
		}; // end class RGB_configType
		
		/**
		 * Definition of Parameter Depth_config
		 */
		class Depth_configType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			int framerate;
			int height;
			int width;
		
		public:
			// default constructor
			Depth_configType() {
				framerate = 30;
				height = 480;
				width = 640;
			}
		
			/**
			 * here are the public getters
			 */
			inline int getFramerate() const { return framerate; }
			inline int getHeight() const { return height; }
			inline int getWidth() const { return width; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "Depth_config(";
				os << "framerate = " << framerate << ", ";
				os << "height = " << height << ", ";
				os << "width = " << width << ", ";
				os << ")\n";
			}
			
		}; // end class Depth_configType
		
		/**
		 * Definition of Parameter base
		 */
		class baseType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			double base_a;
			bool on_base;
			bool on_manipulator;
			bool on_ptu;
			bool on_ur;
			double steer_a;
			int x;
			int y;
			int z;
		
		public:
			// default constructor
			baseType() {
				base_a = 0;
				on_base = false;
				on_manipulator = false;
				on_ptu = false;
				on_ur = false;
				steer_a = 0;
				x = 0;
				y = 0;
				z = 0;
			}
		
			/**
			 * here are the public getters
			 */
			inline double getBase_a() const { return base_a; }
			inline bool getOn_base() const { return on_base; }
			inline bool getOn_manipulator() const { return on_manipulator; }
			inline bool getOn_ptu() const { return on_ptu; }
			inline bool getOn_ur() const { return on_ur; }
			inline double getSteer_a() const { return steer_a; }
			inline int getX() const { return x; }
			inline int getY() const { return y; }
			inline int getZ() const { return z; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "base(";
				os << "base_a = " << base_a << ", ";
				os << "on_base = " << on_base << ", ";
				os << "on_manipulator = " << on_manipulator << ", ";
				os << "on_ptu = " << on_ptu << ", ";
				os << "on_ur = " << on_ur << ", ";
				os << "steer_a = " << steer_a << ", ";
				os << "x = " << x << ", ";
				os << "y = " << y << ", ";
				os << "z = " << z << ", ";
				os << ")\n";
			}
			
		}; // end class baseType
		
	
		///////////////////////////////////////////
		// External params
		///////////////////////////////////////////
		
	
		///////////////////////////////////////////
		// Instance params
		///////////////////////////////////////////
		
	
protected:

	// Internal params
	Depth_configType Depth_config;
	RGB_configType RGB_config;
	baseType base;
	sensor_poseType sensor_pose;
	settingsType settings;
	stereoType stereo;
	
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
	Depth_configType getDepth_config() const {
		return Depth_config;
	}
	RGB_configType getRGB_config() const {
		return RGB_config;
	}
	baseType getBase() const {
		return base;
	}
	sensor_poseType getSensor_pose() const {
		return sensor_pose;
	}
	settingsType getSettings() const {
		return settings;
	}
	stereoType getStereo() const {
		return stereo;
	}
	
	// external param getters
	
	// repo wrapper class getter(s)
	
	// helper method to easily implement output stream in derived classes
	void to_ostream(std::ostream &os = std::cout) const
	{
		// Internal params
		Depth_config.to_ostream(os);
		RGB_config.to_ostream(os);
		base.to_ostream(os);
		sensor_pose.to_ostream(os);
		settings.to_ostream(os);
		stereo.to_ostream(os);
		
		// External params
		
		// Instance params (encapsulated in a wrapper class for each instantiated parameter repository)
	}
};

#endif
