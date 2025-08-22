/************************************ 
 * Simple SerialBus Slave Interface v0.0.1
 * Date: 30.08.2022 | 21:52
 * <Truck Light and function module>
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

#ifndef _SERVO_CONTROL_H_
#define _SERVO_CONTROL_H_

#include "Arduino.h"							// Add base lib
#include <Servo.h>

void controlServo(bool connectionStatus, Servo& servo, uint16_t position, uint8_t outputPin, uint16_t minMicroseconds, uint16_t maxMicroseconds);
uint32_t convertRange(uint32_t signal, uint32_t inMin = 0, uint32_t inMax = 1023, uint32_t outMin = 1020, uint32_t outMax = 1980);
void positionServo(bool connectionStatus, Servo& servo, bool isUp, bool isDown, uint8_t outputPin, uint16_t minMicroseconds, uint16_t maxMicroseconds);

#endif