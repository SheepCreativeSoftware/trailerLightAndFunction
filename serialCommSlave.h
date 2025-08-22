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

#ifndef _SERIAL_COMM_SLAVE_H_
#define _SERIAL_COMM_SLAVE_H_

#include "Arduino.h"							// Add base lib

// Strings for use in getLightData() for better reading
enum LightIdentifier {
	PARK_LIGHT = 0,
	BRAKE_LIGHT = 1,
	REVERSE_LIGHT = 2,
	RIGHT_BLINK = 3,
	LEFT_BLINK = 4,
	AUX_LIGHT = 5,
	BEACON_LIGHT = 6,
	DIMM_LIGHTS = 7
};

enum AdditionalDataIdentifier {
	LEFT_TURN_INDICATOR = 0,
	RIGHT_TURN_INDICATOR = 1,
	HAZARD_STATE = 2
};

enum ServoDataIdentifier {
	SERVO_CHANNEL_1 = 0,
	SERVO_CHANNEL_2 = 1
};

class SerialCommSlave {
public:
    // Establish Serial Communication
    void begin(
		// The Serial Communication Port
		HardwareSerial* _SerialPort,
		// The connection speed
		uint32_t baud,
		// The serial data format
		uint8_t byteFormat,
		// The pin used to enable transmission
		uint8_t _TxEnablePin,
		// The protocol version
		uint8_t _protocolVersion
	);
	// Update Data from serial communication
    uint16_t update();
	// Get Light Data from specific light
    bool getLightData(LightIdentifier lightOption);
	// Get Additional Data from specific option
    bool getAdditionalData(AdditionalDataIdentifier additionalOption);
    // Get Servo Data from specific option
    uint16_t getServoData(ServoDataIdentifier servoOption);
    // Get Connection Status
    bool getConnectionStatus();
    // Get Error Count
    uint16_t getErrorCount();

private:
	// Constants, replacing the #defines
    static constexpr uint8_t BUFFER_SIZE = 64;
    static constexpr uint8_t MIN_BUFFER_SIZE = 4;
    static constexpr uint8_t BUFFER_EMPTY = 0;
    static constexpr uint8_t FUNC_LIGHT_DATA = 1;
    static constexpr uint8_t FUNC_LIGHT_SERVO = 2;
    static constexpr uint16_t MAX_TIME_SIGNAL = 1000;
    static constexpr uint16_t WAIT_FOR_NEXT_BYTE = 1000;
    static constexpr uint8_t BIT_COUNT = 8;
    static constexpr uint16_t POLYNOMIAL = 0xA001;
    // Private helper function
    uint16_t calculateCRC(uint8_t bufferSize);

    // All your former global variables are now private members
    uint8_t frame[BUFFER_SIZE];
    uint8_t TxEnablePin;
    uint8_t protocolVersion = 1;
    uint16_t errorCount = 0;
    HardwareSerial* SerialPort;

    uint8_t lightDataFromSerial = 0;
    uint8_t additionalDataFromSerial = 0;
    uint16_t servoMicrosFromSerial[2] = {0, 0};
    uint32_t lastValidPackage;
    bool connectionLost = true;
};

#endif