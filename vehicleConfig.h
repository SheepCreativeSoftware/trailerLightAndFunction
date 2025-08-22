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

#ifndef _VEHICLE_CONFIG_H_
#define _VEHICLE_CONFIG_H_

#include "Arduino.h"

enum CountryOption {
	US,
	EU
};

enum DebugLevel {
	NONE,
	STATUS_ONLY,
	FUNCTION_STATE,
};

enum ProtocolVersion {
	V1 = 1,
	V2
};

struct GeneralConfig {
	// Setup Region EU or US for Truck - Use `CountryOption` enum
	CountryOption countryOption;
	// Level for debugging - Use `DebugLevel` enum
	DebugLevel debugLevel;
	// Pin for status LED on the Arduino
	uint8_t statusLightPin;
};

struct GeneralLightConfig {
	// Fade in time for all lights
	uint16_t fadeOnTime;
	// Fade out time for all lights
	uint16_t fadeOffTime;
	// Starter Brightness decrease factor
	uint8_t starterDimmingFactor;
	// Starter Brightness decrease multiplier
	uint8_t starterDimmingMultiplier;
};

struct SerialConfig {
	// Enable Serial Communication
	bool isEnabled;
	// Pin for TX Enable on MAX485
	uint8_t outTxEnablePin;
	// Baud rate for Serial Communication (e.g. 19200)
	uint32_t baudRate;
	// e.g. SERIAL_8N1 | start bit, data bit, stop bit
	uint8_t byteFormat;
	// Time to wait for a response
	long timeout;
	// Time between polling requests
	long pollingInterval;
	// Protocol version
	ProtocolVersion protocolVersion;
};

struct LightOutputChannel {
	// Hardware Pin on the Arduino for the Light Output Channel
	uint8_t outputPin;
	// Brightness level for Primary Light Function
	uint8_t primaryOnBrightness;
	// Brightness level for Secondary Light Function
	uint8_t secondaryOnBrightness;
	// Brightness level for Tertiary Light Function
	uint8_t tertiaryOnBrightness;
	// Brightness level for Off Light Function
	uint8_t offBrightness;
	// Fade in time for all lights
	uint16_t fadeOnTime;
	// Fade out time for all lights
	uint16_t fadeOffTime;
};

struct CombinedBrakeTurnSignalLightConfig {
	bool singleLightOption;
};

struct ServoChannel {
	// Hardware Pin on the Arduino for the Servo Channel
	uint8_t outputPin;
	// Minimum angle for the Servo
	uint16_t minMicroseconds;
	// Maximum angle for the Servo
	uint16_t maxMicroseconds;
	// Current angle of the Servo
	uint16_t defaultMicroseconds;
};


struct VehicleConfig {
	GeneralConfig generalConfig;
	GeneralLightConfig generalLightConfig;
	SerialConfig serialConfig;
	LightOutputChannel rearLeftTurnLight;
	LightOutputChannel rearRightTurnLight;
	LightOutputChannel sideLeftTurnLight;
	LightOutputChannel sideRightTurnLight;
	LightOutputChannel parkingLight;
	LightOutputChannel reverseLight;
	LightOutputChannel brakeLight;
	LightOutputChannel auxLight;
	ServoChannel servoChannel1;
	ServoChannel servoChannel2;
	CombinedBrakeTurnSignalLightConfig combinedBrakeTurnSignalLightConfig;
};

#endif