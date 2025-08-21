/************************************ 
 * Copyright (C) 2020-2025 Marina Egner <hello@sheepcs.de>
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

#ifndef _STARTER_BRIGHTNESS_ADJUSTMENT_H_
#define _STARTER_BRIGHTNESS_ADJUSTMENT_H_

#include "Arduino.h"

enum LightType {
    PARKING,
    BRAKE,
    REAR_LEFT_TURN,
    REAR_RIGHT_TURN,
    SIDE_LEFT_TURN,
    SIDE_RIGHT_TURN,
    REVERSE,
    AUX,
	//----
	NUM_LIGHT_TYPES
};

enum LightModes {
    PRIMARY,
    SECONDARY,
    TERTIARY,
	NUM_LIGHT_MODES
};





//Classes
class StarterAdjustedBrightness {
	private:
		bool isStarterActive;
		uint8_t divisor = 5;
		uint8_t multiplier = 2;
		uint8_t brightnessConfig[NUM_LIGHT_TYPES][NUM_LIGHT_MODES];
    public:
		void setupAdjustmentParameters(uint8_t newDivisor, uint8_t newMultiplier);
		void configureBrightnessLevels(LightType type, LightModes mode, uint8_t brightness);
		void setStarterState(bool active);
		uint8_t getBrightnessLevel(LightType type, LightModes mode = PRIMARY);
};

#endif