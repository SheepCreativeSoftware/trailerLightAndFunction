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

//void setupHardwareServo();
//void writeHardwareServo(int microSeconds, int pin, uint16_t minMicroseconds = 1000, uint16_t maxMicroseconds = 2000);

class Servo {
	private:
		uint16_t _threshold;
		uint8_t _attachedServo[2];
		uint16_t _minMicroseconds[2];
		uint16_t _maxMicroseconds[2];
		uint16_t _currentMicroseconds[2];
	public:
		void attach(uint8_t pin, uint16_t minMicroseconds = 1000, uint16_t maxMicroseconds = 2000, uint16_t threshold = 15);
		void writeMicroseconds(uint16_t microSeconds, uint8_t pin);
		void detach(uint8_t pin);
		bool isAttached(uint8_t pin);
};

#endif