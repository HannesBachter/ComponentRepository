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
//  Copyright (C) 2010 Manuel Wopfner, Matthias Lutz
//
//        schlegel@hs-ulm.de
//        lutz@hs-ulm.de
//
//        ZAFH Servicerobotic Ulm
//        University of Applied Sciences
//        Prittwitzstr. 10
//        89075 Ulm
//        Germany
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2.1
//  of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along
//  with this library; if not, write to the Free Software Foundation, Inc.,
//  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//  This work is based on previous work by the folks from PlayerStage.
//
//--------------------------------------------------------------------------

//----------------------------------------------------------------------------
//
// CREDITS:
//
// The code for the amcl algorithm was taken from the
// Playerstage Project, which is distributed under GPL, and you can find at
// http://playerstage.sourceforge.net/
//
// Player - One Hell of a Robot Server
// Copyright (C) 2000
//    Brian Gerkey, Kasper Stoy, Richard Vaughan, & Andrew Howard
//
//----------------------------------------------------------------------------


#include "AmclTask.hh"
#include "SmartAmcl.hh"

#include <iostream>
#include <fstream>

// We use SDL_image to load the image from disk
#include <yaml.h>
#include <cxcore.h>
#include <highgui.h>

AmclTask::AmclTask(SmartACE::SmartComponent *comp) 
:	AmclTaskCore(comp)
{
	std::cout << "constructor AmclTask\n";
	COMP->pf_init_ = false;

}
AmclTask::~AmclTask() 
{
	std::cout << "destructor AmclTask\n";
	COMP->pf_init_ = false;
	map_free(COMP->map_);
	pf_free(COMP->pf_);

	delete COMP->laser_;
	delete COMP->odom_;

}

int AmclTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further


	if(0!=init(COMP->getGlobalState().getGeneral().getYaml_file())){
		std::cout<<"ERROR opening default map!"<<std::endl;
		//std::cout<<"Retry..."<<std::endl;
		//usleep(1000000);
		return 0;
	}

	if(COMP->getGlobalState().getGeneral().getEnable_visualization() == true){
		COMP->h.displayMap(COMP->map_);
		COMP->h.initObjects();
	}


	return 0;
}
int AmclTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel

	if(COMP->amcl_init == false){
		std::cout<<"[AmclTask] filter not initialized --> skip execution sleep(1)"<<std::endl;
		ACE_OS::sleep(ACE_Time_Value(1,0));
		return 0;
	}

	// get new laser scan
	CommBasicObjects::CommMobileLaserScan scan;
	Smart::StatusCode status = COMP->laserServiceIn->getUpdateWait(scan);
	if (status != Smart::SMART_OK) {
		std::cerr << "[AMCL] laser client " << status << "\n";
		ACE_OS::sleep(ACE_Time_Value(0,250000));
		return 0;
	}

	///////////////////////////////////////////
	// check if the sensor plane is parallel to the x-y plane of the base
	arma::vec zAxis(4);
	zAxis(0) = zAxis(1) = 0;
	zAxis(2) = zAxis(3) = 1.0;

	arma::mat sensor_mat = scan.get_sensor_pose().getHomogeneousMatrix(1.0);
	sensor_mat(0, 3) = sensor_mat(1, 3) = sensor_mat(2, 3) = 0; // remove translation from matrix
	zAxis = sensor_mat * zAxis;

	// laser is planar and mounted upside
	bool isPlanar = (zAxis(2) > 0 && fabs(zAxis(0)) < 0.0001 && fabs(zAxis(1)) < 0.0001);

	// laser is planar but mounted upside down
	bool isPlanarFliped  = (zAxis(2) < 0 && fabs(zAxis(0)) < 0.0001 && fabs(zAxis(1)) < 0.0001);
	///////////////////////////////////////////


	if (!isPlanar && ! isPlanarFliped)
	{
		std::cerr << "\033[0;31m" << "ERROR - LASER IS NOT PLANAR -- " << scan.get_sensor_pose() << "\n\033[0m";
		usleep(500000);
	}
	else if (scan.is_scan_valid()) {

		if(COMP->getGlobalState().getGeneral().getEnable_visualization() == true){
			COMP->h.displayBase(scan.get_base_state().get_base_position());
			COMP->h.displayLaserScan(scan);
		}

		{
		    SmartACE::SmartRecursiveGuard pfGuard(COMP->PFMutex);
			pf_vector_t pose;
			pf_vector_t raw_pose;
			pf_vector_t delta = pf_vector_zero();

			// get the current base pose out of the laser scan
			CommBasicObjects::CommBasePose basePos = scan.get_base_state().get_base_position();
			pose.v[0] = basePos.get_x(1.0);
			pose.v[1] = basePos.get_y(1.0);
			pose.v[2] = pi_to_pi(basePos.get_base_azimuth());

			// get the current raw base pose out of the laser scan
			CommBasicObjects::CommBasePose rawBasePos = scan.get_base_state().get_base_raw_position();
			raw_pose.v[0] = rawBasePos.get_x(1.0);
			raw_pose.v[1] = rawBasePos.get_y(1.0);
			raw_pose.v[2] = pi_to_pi(rawBasePos.get_base_azimuth());

			// get the laser pose on the robot
			CommBasicObjects::CommPose3d sensorPose = scan.get_sensor_pose();
			pf_vector_t laser_pose_v;

			laser_pose_v.v[0] = sensorPose.get_x(1.0);
			laser_pose_v.v[1] = sensorPose.get_y(1.0);
			laser_pose_v.v[2] = pi_to_pi(sensorPose.get_azimuth());
			COMP->laser_->SetLaserPose(laser_pose_v);

			//				std::cout << laser_pose_v.v[0] << ", " << laser_pose_v.v[1]
			//						<< ", " << laser_pose_v.v[2] << "\n";

			////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////

			if (COMP->pf_init_) {
				// Compute change in pose
				//delta = pf_vector_coord_sub(pose, pf_odom_pose_);
				delta.v[0] = raw_pose.v[0] - pf_odom_pose_.v[0];
				delta.v[1] = raw_pose.v[1] - pf_odom_pose_.v[1];
				delta.v[2] = angle_diff(raw_pose.v[2], pf_odom_pose_.v[2]);

				// See if we should update the filter
				laser_update_ = fabs(delta.v[0]) > COMP->getGlobalState().getFilter().getUpdate_min_d() ||
								fabs(delta.v[1]) > COMP->getGlobalState().getFilter().getUpdate_min_d() ||
								fabs(delta.v[2]) > COMP->getGlobalState().getFilter().getUpdate_min_alpha();
				if(COMP->getGlobalState().getGeneral().getVerbose() == true){
					std::cout<<"[AmclTask::on_execute()] Scan points: "<<scan.get_scan_size()<<std::endl;
					std::cout<<"[AmclTask::on_execute()] Scan max points : "<<scan.get_max_scan_size()<<std::endl;
					std::cout<<"[AmclTask::on_execute()] Scan res: "<<scan.get_scan_resolution()<<std::endl;

					std::cout<<" pf_odom_pose_: "<< pf_odom_pose_.v[0]<<" " << pf_odom_pose_.v[1]<<" "<< pf_odom_pose_.v[2]<<std::endl;
					std::cout<<" raw_pose: "<< raw_pose.v[0]<<" " << raw_pose.v[1]<<" "<< raw_pose.v[2]<<std::endl;
					std::cout<<" delta: "<< delta.v[0]<<" " << delta.v[1]<<" "<< delta.v[2]<<std::endl;
					if(laser_update_ == true){
						std::cout<<"Above delta --> update filter!"<<std::endl;
					} else {
						std::cout<<"Below delta"<<std::endl;
					}
				}
			}

			bool force_publication = false;
			if (!COMP->pf_init_) {
				// Pose at last filter update
				pf_odom_pose_ = raw_pose;
				 std::cout<<"Init pf_odom_pose_: "<< pf_odom_pose_.v[0]<<" " << pf_odom_pose_.v[1]<<" "<< pf_odom_pose_.v[2]<<std::endl;

				// Filter is now initialized
				COMP->pf_init_ = true;

				laser_update_ = true;
				force_publication = true;
				resample_count_ = 0;
			}
			// If the robot has moved, update the filter
			else if (COMP->pf_init_ && laser_update_) {
				//printf("pose\n");
				//pf_vector_fprintf(pose, stdout, "%.3f");

				AMCLOdomData odata;
				odata.pose = raw_pose;
				// HACK
				// Modify the delta in the action data so the filter gets
				// updated correctly
				odata.delta = delta;
				if(COMP->getGlobalState().getGeneral().getVerbose() == true){
					std::cout << "pose: " << odata.pose.v[0] << ", " << odata.pose.v[1] << ", " << odata.pose.v[2]<< "\n";
					std::cout << "pose: " << odata.delta.v[0] << ", " << odata.delta.v[1] << ", " << odata.delta.v[2]<< "\n";
				}

//					////// DEBUG ///////////
//					 std::stringstream sFileNamePose;
//					 sFileNamePose << "input_pose.txt";
//
//					 std::ofstream fileStreamPose((sFileNamePose.str()).c_str(),std::ios::app);
//					 if(fileStreamPose)
//					 {
//								std::cout<<"file opened\n";
//								fileStreamPose<<"pose: "<<odata.pose.v[0]<<" "<<odata.pose.v[1]<<" "<<odata.pose.v[2]<<" delta: "<< odata.delta.v[0]<<" " << odata.delta.v[1]<<" "<< odata.delta.v[2]<<std::endl;
//					 }
//					 else
//					 {
//					   std::cout<<"error: opening file\n";
//					 }
//					 fileStreamPose.close();
//					 ////// END DEBUG ///////


				// Use the action data to update the filter
				COMP->odom_->UpdateAction(COMP->pf_, (AMCLSensorData*) &odata);

				// Pose at last filter update
				//this->pf_odom_pose = pose;
			}

			////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////

			bool resampled = false;
			//laser_update_ = false;

			// If the robot has moved, update the filter
			if (laser_update_) {
				AMCLLaserData ldata;
				ldata.sensor = COMP->laser_;
				ldata.range_count = scan.get_scan_size();

				if(scan.get_scan_size()<2){
					std::cout<<"[AmclTask]: scan size <2 --> do not use scan!"<<std::endl;
					return 0;
				}

				// Apply range min/max thresholds, if the user supplied them
				double range_min;
				// TODO check max range use
				//ldata.range_max = 2.0;
				ldata.range_max = scan.get_max_distance(1.0);
				range_min = scan.get_min_distance(1.0);

				// The AMCLLaserData destructor will free this memory
				ldata.ranges = new double[ldata.range_count][2];
				double factor = (isPlanarFliped) ? -1 : 1;
				int rIndex = 0;

				for (int i = 0; i < ldata.range_count; i++) {

					if (isPlanarFliped)
						rIndex = ldata.range_count - i - 1;
					else
						rIndex = i;

					// amcl doesn't (yet) have a concept of min range.
					// So we'll map short readings to max range.
					if (scan.get_scan_distance(i, 1.0) <= range_min) {
						ldata.ranges[rIndex][0] = ldata.range_max;
					} else {
						ldata.ranges[rIndex][0] = scan.get_scan_distance(i, 1.0);
					}

					// Compute bearing
					ldata.ranges[rIndex][1] = pi_to_pi(scan.get_scan_angle(i)) * factor;
					if(COMP->getGlobalState().getGeneral().getVerbose() == true){
						printf("laser %d; dist = %.3f; angle = %.3f\n",rIndex,ldata.ranges[rIndex][0],ldata.ranges[rIndex][1]);
					}

				}

				//	////// DEBUG ///////////
				//	 std::stringstream sFileNameLaser;
				//	 sFileNameLaser << "input_laser.txt";
				//
				//	 std::ofstream fileStreamLaser((sFileNameLaser.str()).c_str(),std::ios::app);
				//	 if(fileStreamLaser)
				//	 {
				//		fileStreamLaser<<"New Timestep"<<std::endl;
				//		for(int i=0;i<ldata.range_count;i++)
				//		{
				//				fileStreamLaser<<"range: "<<ldata.ranges[i][0]<<" bearing: "<<ldata.ranges[i][1]<<std::endl;
				//		 }
				//	 }
				//	 fileStreamLaser.close();
				//	 ////// END DEBUG ///////

				COMP->laser_->UpdateSensor(COMP->pf_, (AMCLSensorData*) &ldata);
				laser_update_ = false;

				pf_odom_pose_ = raw_pose;

				// Resample the particles
				if (!(++resample_count_ % resample_interval_)) {
					std::cout << ">>> do resample\n";
					pf_update_resample(COMP->pf_);
					resampled = true;
				}

				pf_sample_set_t* set = COMP->pf_->sets + COMP->pf_->current_set;

				if(COMP->getGlobalState().getGeneral().getEnable_visualization() == true){
					// display particles
					COMP->h.displayParticles(set);
				}

				// INFO: Here the resulting particle cloud can be published.
			}

			////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////

			if (resampled || force_publication) {

				// Read out the current hypotheses
				double max_weight = 0.0;
				int max_weight_hyp = -1;
				std::vector<amcl_hyp_t> hyps;
				hyps.resize(COMP->pf_->sets[COMP->pf_->current_set].cluster_count);

				for (int hyp_count = 0; hyp_count < COMP->pf_->sets[COMP->pf_->current_set].cluster_count; hyp_count++) {
					double weight;
					pf_vector_t pose_mean;
					pf_matrix_t pose_cov;

					if (!pf_get_cluster_stats(COMP->pf_, hyp_count, &weight, &pose_mean, &pose_cov)) {
						std::cerr << "Couldn't get stats on cluster " << hyp_count << "\n";
						break;
					}

					hyps[hyp_count].weight = weight;
					hyps[hyp_count].pf_pose_mean = pose_mean;
					hyps[hyp_count].pf_pose_cov = pose_cov;

					if (hyps[hyp_count].weight > max_weight) {
						max_weight = hyps[hyp_count].weight;
						max_weight_hyp = hyp_count;
					}
				}

				if(COMP->getGlobalState().getGeneral().getEnable_visualization() == true){
					COMP->h.displayHypotheses(hyps);
				}

				if (max_weight > 0.0) {


//							if(COMP->ini.general.enable_visualization == true){
//								CPose3D pose_tmp(hyps[max_weight_hyp].pf_pose_mean.v[0],
//																		hyps[max_weight_hyp].pf_pose_mean.v[1],0,hyps[max_weight_hyp].pf_pose_mean.v[2],0,0);
//								COMP->h.displayCoordinateSystem(pose_tmp,0.5);
//							}


					printf("Max weight pose: %.3f %.3f %.3f \n", hyps[max_weight_hyp].pf_pose_mean.v[0],
							hyps[max_weight_hyp].pf_pose_mean.v[1], hyps[max_weight_hyp].pf_pose_mean.v[2]);

					Eigen::Matrix3d X = Eigen::Map<Eigen::Matrix3d>(&hyps[max_weight_hyp].pf_pose_cov.m[0][0]);
					Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> es;
					es.compute(X);
					std::cout<<"EigenValues: "<<es.eigenvalues()<<std::endl;
					Eigen::Vector3d eigenvalues = es.eigenvalues();
					double lamda_sum = eigenvalues.sum();
					std::cout<<"The sum of the EigenValues is: "<<lamda_sum<<std::endl;

					CommLocalizationObjects::LocalizationEventState state;
					if(COMP->pf_->sets[COMP->pf_->current_set].cluster_count >COMP->getGlobalState().getGeneral().getLostEventMaxHypothese() || lamda_sum > COMP->getGlobalState().getGeneral().getLostEventMaxEigValueSum())
					{
						std::cout<<"LOCALIZATION LOST!"<<std::endl;
						state.set(CommLocalizationObjects::LocalizationEventType::LOCALIZATION_LOST);
						COMP->localizationEventServiceOut->put(state);



					}
					else
					{
						std::cout<<"LOCALIZATION OK!"<<std::endl;
						state.set(CommLocalizationObjects::LocalizationEventType::LOCALIZATION_OK);
						COMP->localizationEventServiceOut->put(state);
					}


					CommBasicObjects::CommBasePositionUpdate positionUpdate;

					// set base position when the filter was applied
					positionUpdate.set_time_stamp(CommBasicObjects::CommTimeStamp::now());
					positionUpdate.set_old_position(basePos);

					// calculate the corrected base position
					CommBasicObjects::CommBasePose correctedPos;
					correctedPos.set_x(hyps[max_weight_hyp].pf_pose_mean.v[0], 1.0);
					correctedPos.set_y(hyps[max_weight_hyp].pf_pose_mean.v[1], 1.0);
					correctedPos.set_z(basePos.get_z()); // use the z value from the old pos because we do not know better
					correctedPos.set_base_azimuth(hyps[max_weight_hyp].pf_pose_mean.v[2]);

					// Copy in the covariance
					// TODO check covariance matrix
					pf_sample_set_t* set = COMP->pf_->sets + COMP->pf_->current_set;
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < 2; j++) {
							correctedPos.set_cov(i, j, set->cov.m[i][j]);
						}
					}
					correctedPos.set_cov(2, 2, set->cov.m[2][2]);

					printf("New pose: %6.3f %6.3f %6.3f \n", hyps[max_weight_hyp].pf_pose_mean.v[0],
							hyps[max_weight_hyp].pf_pose_mean.v[1], hyps[max_weight_hyp].pf_pose_mean.v[2]);

					// send the position update
					positionUpdate.set_corrected_position(correctedPos);
					COMP->localizationUpdateServiceOut->send(positionUpdate);
				} else {
					std::cerr << "No pose!\n";
				}
			}

		} //pfGuard.release();
	} //if (scan.is_scan_valid())
	else {
		std::cout<<"[AmclTask::on_execute] Got invalid scan!"<<std::endl;
	}

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int AmclTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}


/////////////////////////////////////////////
//
//			private methods
//
/////////////////////////////////////////////

int AmclTask::init(const std::string& mapFilename) {


//	 //DEBUG//
//	 std::stringstream sFileNameLaser;
//	 sFileNameLaser << "input_laser.txt";
//	 std::stringstream sFileNamePose;
//	 sFileNamePose << "input_pose.txt";
//
//	 std::ofstream fileStreamLaser((sFileNameLaser.str()).c_str(),std::ios::trunc);
//	 std::ofstream fileStreamPose((sFileNamePose.str()).c_str(),std::ios::trunc);
//	 fileStreamLaser.close();
//	 fileStreamPose.close();
//	 //END DEBUG//

	std::cout << "[AMCL] loading map ...\n";

	resample_interval_ = COMP->getGlobalState().getFilter().getResample_interval();

	// load yaml file
	std::string fname = mapFilename;
	std::ifstream fin(fname.c_str());
	if (fin.fail()) {
		std::cerr << "[AMCL] Could not open " << fname << "\n";
		return -1;
	}

	YAML::Parser parser(fin);
	YAML::Node doc;
	parser.GetNextDocument(doc);

	double res;
	int negate;
	double occ_th, free_th;
	std::string mapfname = "";
	double origin[3];

	try {
		doc["resolution"] >> res;
	} catch (YAML::InvalidScalar) {
		std::cerr << "[AMCL] The map does not contain a resolution tag or it is invalid.\n";
		return -1;
	}
	try {
		doc["negate"] >> negate;
	} catch (YAML::InvalidScalar) {
		std::cerr << "[AMCL] The map does not contain a negate tag or it is invalid.\n";
		return -1;
	}
	try {
		doc["occupied_thresh"] >> occ_th;
	} catch (YAML::InvalidScalar) {
		std::cerr << "[AMCL] The map does not contain an occupied_thresh tag or it is invalid.\n";
		return -1;
	}
	try {
		doc["free_thresh"] >> free_th;
	} catch (YAML::InvalidScalar) {
		std::cerr << "[AMCL] The map does not contain a free_thresh tag or it is invalid.\n";
		return -1;
	}
	try {
		doc["origin"][0] >> origin[0];
		doc["origin"][1] >> origin[1];
		doc["origin"][2] >> origin[2];
	} catch (YAML::InvalidScalar) {
		std::cerr << "[AMCL] The map does not contain an origin tag or it is invalid.\n";
		return -1;
	}
	try {
		doc["image"] >> mapfname;
		// TODO: make this path-handling more robust
		if (mapfname.size() == 0) {
			std::cerr << "[AMCL] The image tag cannot be an empty string.\n";
			return -1;
		}
		if (mapfname[0] != '/') {
			// dirname can modify what you pass it
			char* fname_copy = strdup(fname.c_str());
			mapfname = std::string(dirname(fname_copy)) + '/' + mapfname;
			free(fname_copy);
		}
	} catch (YAML::InvalidScalar) {
		std::cerr << "[AMCL] The map does not contain an image tag or it is invalid.\n";
		return -1;
	}

	SmartACE::SmartRecursiveGuard pfGuard(COMP->PFMutex);
	{
		if(COMP->amcl_init == true){
			std::cout << "WARNING [AMCL] initializing filter --> filter already initialized ... DO NOTHING\n";
			return 0;
		}

		std::cout << "[AMCL] loading map from file ...\n";
		// load map
		COMP->map_ = loadMapFromFile(mapfname, res, negate, occ_th, free_th, origin);

		std::cout << "[AMCL] initializing filter ...\n";
		ParameterStateStruct localState = COMP->getGlobalState();

		// Create the particle filter
		COMP->pf_ = pf_alloc(localState.getFilter().getMin_particles(), localState.getFilter().getMax_particles(),
				localState.getFilter().getRecovery_alpha_slow(), localState.getFilter().getRecovery_alpha_fast(),
				(pf_init_model_fn_t) SmartAmclCore::uniformPoseGenerator, (void *) COMP->map_);

		COMP->pf_->pop_err = localState.getFilter().getKld_err();
		COMP->pf_->pop_z = localState.getFilter().getKld_z();


		if(localState.getGeneral().getInitalizationType() == ParameterStateStruct::GeneralType::initalizationTypeType::INI_POSE){
			// Initialize the filter
			pf_vector_t pf_init_pose_mean = pf_vector_zero();
			pf_init_pose_mean.v[0] = localState.getGeneral().getInitial_x();
			pf_init_pose_mean.v[1] = localState.getGeneral().getInitial_y();
			pf_init_pose_mean.v[2] = localState.getGeneral().getInitial_a();
			pf_matrix_t pf_init_pose_cov = pf_matrix_zero();
			pf_init_pose_cov.m[0][0] = localState.getGeneral().getInitial_cov_xx();
			pf_init_pose_cov.m[1][1] = localState.getGeneral().getInitial_cov_yy();
			pf_init_pose_cov.m[2][2] = localState.getGeneral().getInitial_cov_aa();
			pf_init(COMP->pf_, pf_init_pose_mean, pf_init_pose_cov);

		} else if (localState.getGeneral().getInitalizationType() == ParameterStateStruct::GeneralType::initalizationTypeType::GLOBAL){
			pf_init_model(COMP->pf_,(pf_init_model_fn_t) SmartAmclCore::uniformPoseGenerator, (void *) COMP->map_);

		} else if (localState.getGeneral().getInitalizationType() == ParameterStateStruct::GeneralType::initalizationTypeType::FILE_POSE){

			ifstream file (localState.getGeneral().getInitPoseFileName().c_str());
			if (file.is_open())
			{
				std::string line;
				getline (file,line);

				std::cout<<"line: "<<line<<std::endl;
				std::stringstream ss(line);
				std::stringstream tmp;
				std::string token;
				double x,y,a;

				tmp.clear();
				std::getline(ss, token, ';');
				tmp.str(token);
				tmp>>x;

				tmp.clear();
				std::getline(ss, token, ';');
				tmp.str(token);
				tmp>>y;

				tmp.clear();
				std::getline(ss, token, ';');
				tmp.str(token);
				tmp>>a;

				std::cout<<"Pose from file x:"<<x<<" y:"<<y<<" a:"<<a<<std::endl;

				pf_vector_t pf_init_pose_mean = pf_vector_zero();
				pf_init_pose_mean.v[0] = x;
				pf_init_pose_mean.v[1] = y;
				pf_init_pose_mean.v[2] = a;
				pf_matrix_t pf_init_pose_cov = pf_matrix_zero();
				pf_init_pose_cov.m[0][0] = localState.getGeneral().getInitial_cov_xx();
				pf_init_pose_cov.m[1][1] = localState.getGeneral().getInitial_cov_yy();
				pf_init_pose_cov.m[2][2] = localState.getGeneral().getInitial_cov_aa();
				pf_init(COMP->pf_, pf_init_pose_mean, pf_init_pose_cov);

			} else {
				std::cout<<"Error opening file: "<<localState.getGeneral().getInitPoseFileName()<<std::endl;
				std::cout<<"USE GLOBAL LOCLIZATION"<<std::endl;
				pf_init_model(COMP->pf_,(pf_init_model_fn_t) SmartAmclCore::uniformPoseGenerator, (void *) COMP->map_);
			}
		}

		//pf_init_model(pf_, (pf_init_model_fn_t) AmclTask::uniformPoseGenerator, (void *) map_);
		COMP->pf_init_ = false;

		// Instantiate the sensor objects
		// Odometry
		odom_model_t odom_model_type;
		if(localState.getOdometry().getOdom_model_type() == "diff"){
			odom_model_type = ODOM_MODEL_DIFF;
		}else if (localState.getOdometry().getOdom_model_type() == "omni"){
			odom_model_type = ODOM_MODEL_OMNI;
		}else{
			std::cout<<"Unkown odom model type "<<localState.getOdometry().getOdom_model_type()<< " defaulting to diff model"<<std::endl;
			odom_model_type = ODOM_MODEL_DIFF;

		}

		COMP->odom_ = new AMCLOdom();
		if(odom_model_type == ODOM_MODEL_OMNI){
			COMP->odom_->SetModelOmni(localState.getOdometry().getAlpha1(), localState.getOdometry().getAlpha2(), localState.getOdometry().getAlpha3(),
					localState.getOdometry().getAlpha4(), localState.getOdometry().getAlpha5());
		}else {
			COMP->odom_->SetModelDiff(localState.getOdometry().getAlpha1(), localState.getOdometry().getAlpha2(), localState.getOdometry().getAlpha3(),
					localState.getOdometry().getAlpha4());
		}

		// Laser
		laser_model_t laser_model_type;
		if(localState.getLaser().getLaser_model_type() == "beam"){
			laser_model_type = LASER_MODEL_BEAM;
		}else if(localState.getLaser().getLaser_model_type() == "likelihood_field"){
			laser_model_type = LASER_MODEL_LIKELIHOOD_FIELD;
		}else{
			std::cout<<"Unkown laser model type "<<localState.getLaser().getLaser_model_type()<< " defaulting to likelihood_field model"<<std::endl;
			laser_model_type = LASER_MODEL_LIKELIHOOD_FIELD;
		}


		COMP->laser_ = new AMCLLaser(localState.getLaser().getMax_beams(), COMP->map_);
		if(laser_model_type == LASER_MODEL_BEAM){
			COMP->laser_->SetModelBeam(localState.getLaser().getZ_hit(), localState.getLaser().getZ_short(), localState.getLaser().getZ_max(),
					localState.getLaser().getZ_rand(), localState.getLaser().getSigma_hit(), localState.getLaser().getLambda_short(), 0.0);
		}else{
			COMP->laser_->SetModelLikelihoodField(localState.getLaser().getZ_hit(), localState.getLaser().getZ_rand(), localState.getLaser().getSigma_hit(),
					localState.getLaser().getLaser_likelihood_max_dist());
		}

	}
	COMP->amcl_init = true;
	pfGuard.release();

	std::cout << "[AMCL] init finished!\n";
	return 0;
}

map_t* AmclTask::loadMapFromFile(const std::string& fname, double res, bool negate, double occ_th, double free_th,
		double* origin) {

	unsigned char* pixels;
	unsigned char* p;
	int rowstride, n_channels;
	int i, j;
	int k;
	double occ;
	int color_sum;
	double color_avg;

	map_t* map = map_alloc();
	IplImage* img = NULL;




	// Load the image using SDL.  If we get NULL back, the image load failed.
	if (!(img = cvLoadImage(fname.c_str(), CV_LOAD_IMAGE_UNCHANGED))) {
		std::string errmsg = std::string("failed to open image file \"") + fname + std::string("\"");
		throw std::runtime_error(errmsg);
	}

	map->size_x = img->width;
	map->size_y = img->height;
	map->scale = res;
	std::cout<<" origin[0]"<<origin[0]<<std::endl;
	std::cout<<" origin[1]"<<origin[1]<<std::endl;
	map->origin_x = origin[0] + (map->size_x / 2.0) * map->scale;
	map->origin_y = origin[1] + (map->size_y / 2.0) * map->scale;
	map->cells = (map_cell_t*) malloc(sizeof(map_cell_t) * map->size_x * map->size_y);

	// Get values that we'll need to iterate through the pixels
	rowstride = img->widthStep;
	n_channels = img->nChannels;

	// Copy pixel data into the map structure
	pixels = (unsigned char*) (img->imageData);

	for (j = 0; j < img->height; j++) {
		for (i = 0; i < img->width; i++) {

			// Compute mean of RGB for this pixel
			p = pixels + j * rowstride + i * n_channels;
			color_sum = 0;
			for (k = 0; k < n_channels; k++) {
				color_sum += *(p + (k));
			}
			color_avg = color_sum / (double) n_channels;

			// If negate is true, we consider blacker pixels free, and whiter
			// pixels free.  Otherwise, it's vice versa.
			if (negate) {
				occ = color_avg / 255.0;
			} else {
				occ = (255 - color_avg) / 255.0;
			}

			// Apply thresholds to RGB means to determine occupancy values for
			// map.  Note that we invert the graphics-ordering of the pixels to
			// produce a map with cell (0,0) in the lower-left corner.
			if (occ > occ_th) {
				map->cells[MAP_IDX(img->width, i, img->height - j - 1)].occ_state = +1;
			} else if (occ < free_th) {
				map->cells[MAP_IDX(img->width, i, img->height - j - 1)].occ_state = -1;
			} else {
				map->cells[MAP_IDX(img->width, i, img->height - j - 1)].occ_state = 0;
			}
		}
	}
	cvReleaseImage(&img);

	return map;
}


