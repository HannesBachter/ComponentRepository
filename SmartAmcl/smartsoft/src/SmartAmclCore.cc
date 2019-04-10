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

#include "SmartAmclCore.hh"

#include <stdlib.h>


// constructor
SmartAmclCore::SmartAmclCore():amcl_init(false)
{
	std::cout << "constructor SmartAmclCore\n";


}

pf_vector_t SmartAmclCore::uniformPoseGenerator(void* arg) {
	map_t* map = (map_t*) arg;
	double min_x, max_x, min_y, max_y;

	// CHANGED: added - to min_x and min_y
	min_x = -(map->size_x * map->scale) / 2.0 - map->origin_x;
	max_x = (map->size_x * map->scale) / 2.0 + map->origin_x;
	min_y = -(map->size_y * map->scale) / 2.0 - map->origin_y;
	max_y = (map->size_y * map->scale) / 2.0 + map->origin_y;

	pf_vector_t p;

	for (;;) {
		p.v[0] = min_x + drand48() * (max_x - min_x);
		p.v[1] = min_y + drand48() * (max_y - min_y);
		p.v[2] = drand48() * 2 * M_PI - M_PI;

		// Check that it's a free cell
		int i, j;
		i = MAP_GXWX(map, p.v[0]);
		j = MAP_GYWY(map, p.v[1]);
		if (MAP_VALID(map,i,j) && (map->cells[MAP_INDEX(map,i,j)].occ_state == -1)) {
			break;
		}
	}

	return p;
}
