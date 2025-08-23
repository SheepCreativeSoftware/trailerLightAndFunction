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

#include "vehicleConfig.h"

/************************************
 * Configuration Programm
 ************************************/

VehicleConfig vehicleConfig = {
	.generalConfig = {
		.countryOption = CountryOption::US,
		.debugLevel = DebugLevel::STATUS_ONLY,
		.statusLightPin = 13
	},
	.generalLightConfig = {
		.fadeOnTime = 200,
		.fadeOffTime = 200,
		.starterDimmingFactor = 5,
		.starterDimmingMultiplier = 2
	},
	.serialConfig = {
		.isEnabled = true,
		.outTxEnablePin = 2,
		.baudRate = 19200,
		.byteFormat = SERIAL_8N1,
		.timeout = 1000,
		.pollingInterval = 20,
		.protocolVersion = ProtocolVersion::V2
	},
	.rearLeftTurnLight = {
		.outputPin = 5,
		.primaryOnBrightness = 255,
		// Parking when combined
		.secondaryOnBrightness = 15,
		.tertiaryOnBrightness = 0,
		.offBrightness = 0,
		.fadeOnTime = 200,
		.fadeOffTime = 200
	},
	.rearRightTurnLight = {
		.outputPin = 4,
		.primaryOnBrightness = 255,
		// Parking when combined
		.secondaryOnBrightness = 15,
		.tertiaryOnBrightness = 0,
		.offBrightness = 0,
		.fadeOnTime = 200,
		.fadeOffTime = 200
	},
	.sideLeftTurnLight = {
		.outputPin = 7,
		.primaryOnBrightness = 255,
		.secondaryOnBrightness = 0,
		.tertiaryOnBrightness = 0,
		.offBrightness = 0,
		.fadeOnTime = 200,
		.fadeOffTime = 200
	},
	.sideRightTurnLight = {
		.outputPin = 6,
		.primaryOnBrightness = 255,
		.secondaryOnBrightness = 0,
		.tertiaryOnBrightness = 0,
		.offBrightness = 0,
		.fadeOnTime = 200,
		.fadeOffTime = 200
	},
	.parkingLight = {
		.outputPin = 8,
		.primaryOnBrightness = 255,
		.secondaryOnBrightness = 0,
		.tertiaryOnBrightness = 0,
		.offBrightness = 0,
		.fadeOnTime = 200,
		.fadeOffTime = 200
	},
	.reverseLight = {
		.outputPin = 3,
		.primaryOnBrightness = 255,
		.secondaryOnBrightness = 0,
		.tertiaryOnBrightness = 0,
		.offBrightness = 0,
		.fadeOnTime = 200,
		.fadeOffTime = 200
	},
	.brakeLight = {
		.outputPin = 11,
		.primaryOnBrightness = 255,
		// Parking when combined
		.secondaryOnBrightness = 15,
		.tertiaryOnBrightness = 0,
		.offBrightness = 0,
		.fadeOnTime = 200,
		.fadeOffTime = 200
	},
	.auxLight = {
		.outputPin = 12,
		.primaryOnBrightness = 255,
		.secondaryOnBrightness = 0,
		.tertiaryOnBrightness = 0,
		.offBrightness = 0,
		.fadeOnTime = 200,
		.fadeOffTime = 200
	},
	.servoChannel1 = {
		.outputPin = 9,
		.minMicroseconds = 1020,
		.maxMicroseconds = 2020,
		.defaultMicroseconds = 1520
	},
	.servoChannel2 = {
		.outputPin = 10,
		.minMicroseconds = 1200,
		.maxMicroseconds = 1900,
		.defaultMicroseconds = 1520
	},
	.combinedBrakeTurnSignalLightConfig = {
		.singleLightOption = true
	}
};

#define DEBUGLEVEL vehicleConfig.generalConfig.debugLevel

#endif