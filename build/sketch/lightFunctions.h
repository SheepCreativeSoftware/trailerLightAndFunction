#line 1 "/home/magraina/projects/trailerLightAndFunction/lightFunctions.h"
/************************************ 
 * Copyright (C) 2022 Marina Egner <info@sheepindustries.de>
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

#ifndef _LIGHT_FUNCTIONS_H_
#define _LIGHT_FUNCTIONS_H_

#include "Arduino.h"
#include <SoftPWM.h>

#define SOFT_PWM_HIGH 255
#define SOFT_PWM_LOW 0

//Functions
void initLightOutput();			// Init SoftPWM Lib
void setupLightOutput(uint8_t pin, uint16_t fadeOnTime, uint16_t fadeOffTime); // Create and set pin | Set fade up and down time for pin
void setBooleanLight(uint8_t pin, bool state, uint8_t highValue = SOFT_PWM_HIGH);
uint8_t starterDimming(bool active, uint8_t defaultDimValue, uint8_t divisor, uint8_t multiplier1);
void setBrakingWithPark(uint8_t pin, uint8_t parkState, uint8_t brakeState, uint8_t parkDimming, uint8_t highValue = SOFT_PWM_HIGH);

#endif