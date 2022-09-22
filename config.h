/************************************ 
 * Copyright (C) 2022 Marina Egner <info@sheepCreativeStudios.de>
 *
 * This program is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. 
 * If not, see <https://www.gnu.org/licenses/>.
 ************************************/

#ifndef _CONFIG_H_
#define _CONFIG_H_

/************************************
 * Configuration Programm
 ************************************/
#define COUNTRY_OPTION EU						//Setup Region EU or US for Truck
#define LIGHT_FADE_ON_TIME 200				// 200ms Fade on time for the Light
#define LIGHT_FADE_OFF_TIME 200				// 200ms Fade off time for the Light
#define NORMAL_LIGHT_DIMMING 255			// 0-255 Value for all light when active
#define STARTER_DIMM_DIVISOR 5				// Divisor for Dimming function
#define STARTER_DIMM_MULTI1 2				// 0-255 MAX Value for all light when active starter is activ
#define BRAKE_IS_PARKING true				// 
#define BRAKE_PARK_DIMM	50
#define SERIAL_COM true							// Activate Communication to other modules via Serial 

//Change this value for different debuging levels
#define DEBUGLEVEL 1						////1 = Status LED | >2 = Serial Monitor

#endif