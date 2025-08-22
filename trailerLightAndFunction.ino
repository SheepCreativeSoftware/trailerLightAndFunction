/************************************ 
 * trailerLightAndFunction v0.1.0
 * Date: 18.09.2020 | 12:08
 * by M.Egner
 * <Trailer Module for Truck Light and function module>
 * Copyright (C) 2020 Marina Egner <info@sheepindustries.de>
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

/************************************
 * Configuration Programm
 ************************************/
#include "config.h"

/************************************
 * Include Files
 ************************************/
#include "serialCommSlave.h"
#include "lightFunctions.h"
#include "starterBrightnessAdjustment.h"
#include <Servo.h>
#include "servoControl.h"

/************************************
 * Definition and Initialisation 
 * Global Vars, Classes and Functions
 ************************************/
//Setup Serial and check if Board is UNO with one Serial or Leonardo/Micro with to Serials
#ifdef HAVE_HWSERIAL1								//if serial ports 1 exist then the arduino has more than one serial port
	#ifndef SerialUSB								//if not allready defined
		#define SerialUSB SERIAL_PORT_MONITOR		//then define monitor port
	#endif
#else
	#define DEBUGLEVEL 1
#endif
#ifndef SerialHW									//if not allready defined
	#define SerialHW SERIAL_PORT_HARDWARE			//then define hardware port
#endif

bool pulseStatus = false;
uint32_t StatusPreviousMillis = 0;
uint32_t blinkOnTime = 0;
bool serialIsSent[1] = { false };

SerialCommSlave truckSerial;
StarterAdjustedBrightness brightnessAdjust;
Servo servoChannel1;
Servo servoChannel2;

//Functions
bool controllerStatus(bool);
uint8_t blink(uint16_t);

void setup() {
	if (vehicleConfig.serialConfig.isEnabled == true) {
	truckSerial.begin(&SerialHW,
					vehicleConfig.serialConfig.baudRate,
					vehicleConfig.serialConfig.byteFormat,
					vehicleConfig.serialConfig.outTxEnablePin,
					vehicleConfig.serialConfig.protocolVersion
	);
	}
	if (DEBUGLEVEL >= 2) {
		pinMode(vehicleConfig.generalConfig.statusLightPin, OUTPUT);
	}
	initLightOutput();			// Init SoftPWM Lib
	setupLightOutput(
		vehicleConfig.parkingLight.outputPin,
		vehicleConfig.parkingLight.fadeOnTime,
		vehicleConfig.parkingLight.fadeOffTime
	);
	setupLightOutput(
		vehicleConfig.sideLeftTurnLight.outputPin,
		vehicleConfig.sideLeftTurnLight.fadeOnTime,
		vehicleConfig.sideLeftTurnLight.fadeOffTime
	);
	setupLightOutput(
		vehicleConfig.sideRightTurnLight.outputPin,
		vehicleConfig.sideRightTurnLight.fadeOnTime,
		vehicleConfig.sideRightTurnLight.fadeOffTime
	);
	setupLightOutput(
		vehicleConfig.rearLeftTurnLight.outputPin,
		vehicleConfig.rearLeftTurnLight.fadeOnTime,
		vehicleConfig.rearLeftTurnLight.fadeOffTime
	);
	setupLightOutput(
		vehicleConfig.rearRightTurnLight.outputPin,
		vehicleConfig.rearRightTurnLight.fadeOnTime,
		vehicleConfig.rearRightTurnLight.fadeOffTime
	);
	setupLightOutput(
		vehicleConfig.reverseLight.outputPin,
		vehicleConfig.reverseLight.fadeOnTime,
		vehicleConfig.reverseLight.fadeOffTime
	);
	setupLightOutput(
		vehicleConfig.brakeLight.outputPin,
		vehicleConfig.brakeLight.fadeOnTime,
		vehicleConfig.brakeLight.fadeOffTime
	);
	setupLightOutput(
		vehicleConfig.auxLight.outputPin,
		vehicleConfig.auxLight.fadeOnTime,
		vehicleConfig.auxLight.fadeOffTime
	);

	// Initialize brightness adjustment
	brightnessAdjust.setupAdjustmentParameters(vehicleConfig.generalLightConfig.starterDimmingFactor, vehicleConfig.generalLightConfig.starterDimmingMultiplier);
	brightnessAdjust.configureBrightnessLevels(LightType::PARKING, LightModes::PRIMARY, vehicleConfig.parkingLight.primaryOnBrightness);
	brightnessAdjust.configureBrightnessLevels(LightType::REAR_LEFT_TURN, LightModes::PRIMARY, vehicleConfig.rearLeftTurnLight.primaryOnBrightness);
	brightnessAdjust.configureBrightnessLevels(LightType::REAR_LEFT_TURN, LightModes::SECONDARY, vehicleConfig.rearLeftTurnLight.secondaryOnBrightness);
	brightnessAdjust.configureBrightnessLevels(LightType::REAR_RIGHT_TURN, LightModes::PRIMARY, vehicleConfig.rearRightTurnLight.primaryOnBrightness);
	brightnessAdjust.configureBrightnessLevels(LightType::REAR_RIGHT_TURN, LightModes::SECONDARY, vehicleConfig.rearRightTurnLight.secondaryOnBrightness);
	brightnessAdjust.configureBrightnessLevels(LightType::SIDE_LEFT_TURN, LightModes::PRIMARY, vehicleConfig.sideLeftTurnLight.primaryOnBrightness);
	brightnessAdjust.configureBrightnessLevels(LightType::SIDE_RIGHT_TURN, LightModes::PRIMARY, vehicleConfig.sideRightTurnLight.primaryOnBrightness);
	brightnessAdjust.configureBrightnessLevels(LightType::REVERSE, LightModes::PRIMARY, vehicleConfig.reverseLight.primaryOnBrightness);
	brightnessAdjust.configureBrightnessLevels(LightType::BRAKE, LightModes::PRIMARY, vehicleConfig.brakeLight.primaryOnBrightness);
	brightnessAdjust.configureBrightnessLevels(LightType::BRAKE, LightModes::SECONDARY, vehicleConfig.brakeLight.secondaryOnBrightness);
	brightnessAdjust.configureBrightnessLevels(LightType::AUX, LightModes::PRIMARY, vehicleConfig.auxLight.primaryOnBrightness);
}

void loop() {
	bool errorFlag = false;

	/*
	 * Update the serial communication
	 */

	if (vehicleConfig.serialConfig.isEnabled == true) {
		truckSerial.update();
	}

	bool parkLightState = truckSerial.getLightData(LightIdentifier::PARK_LIGHT);
	bool brakeLightState = truckSerial.getLightData(LightIdentifier::BRAKE_LIGHT);
	bool reverseLightState = truckSerial.getLightData(LightIdentifier::REVERSE_LIGHT);
	bool rightTurnIndicatorState = truckSerial.getLightData(LightIdentifier::RIGHT_BLINK);
	bool leftTurnIndicatorState = truckSerial.getLightData(LightIdentifier::LEFT_BLINK);
	bool auxLightState = truckSerial.getLightData(LightIdentifier::AUX_LIGHT);
	bool beaconLightState = truckSerial.getLightData(LightIdentifier::BEACON_LIGHT);
	bool isStarterActive = truckSerial.getLightData(LightIdentifier::DIMM_LIGHTS);
	bool isLeftTurnIndicatorActive = truckSerial.getAdditionalData(AdditionalDataIdentifier::LEFT_TURN_INDICATOR);
	bool isRightTurnIndicatorActive = truckSerial.getAdditionalData(AdditionalDataIdentifier::RIGHT_TURN_INDICATOR);
	bool isHazardActive = truckSerial.getAdditionalData(AdditionalDataIdentifier::HAZARD_STATE);

	uint16_t servoChannel1Position = truckSerial.getServoData(ServoDataIdentifier::SERVO_CHANNEL_1);
	uint16_t servoChannel2Position = truckSerial.getServoData(ServoDataIdentifier::SERVO_CHANNEL_2);

	bool connectionStatus = truckSerial.getConnectionStatus();
	if (connectionStatus == false) errorFlag = true;

	/*
	 * Update the servo control
	 */

	controlServo(
		connectionStatus,
		servoChannel1,
		servoChannel1Position,
		vehicleConfig.servoChannel1.outputPin,
		vehicleConfig.servoChannel1.minMicroseconds,
		vehicleConfig.servoChannel1.maxMicroseconds
	);

	controlServo(
		connectionStatus,
		servoChannel2,
		servoChannel2Position,
		vehicleConfig.servoChannel2.outputPin,
		vehicleConfig.servoChannel2.minMicroseconds,
		vehicleConfig.servoChannel2.maxMicroseconds
	);

	/*
	 * Update the lights
	 */

	setBooleanLight(
		vehicleConfig.parkingLight.outputPin,
		parkLightState, 
		brightnessAdjust.getBrightnessLevel(LightType::PARKING)
	);
	
	setBooleanLight(
		vehicleConfig.sideLeftTurnLight.outputPin,
		leftTurnIndicatorState,
		brightnessAdjust.getBrightnessLevel(LightType::SIDE_LEFT_TURN)
	);
	setBooleanLight(
		vehicleConfig.sideRightTurnLight.outputPin,
		rightTurnIndicatorState,
		brightnessAdjust.getBrightnessLevel(LightType::SIDE_RIGHT_TURN)
	);
	setBooleanLight(
		vehicleConfig.reverseLight.outputPin,
		reverseLightState,
		brightnessAdjust.getBrightnessLevel(LightType::REVERSE)
	);
	setBooleanLight(
		vehicleConfig.auxLight.outputPin,
		auxLightState,
		brightnessAdjust.getBrightnessLevel(LightType::AUX)
	);

	switch (vehicleConfig.generalConfig.countryOption) {
		case CountryOption::EU:	// Option for EU needed
			setBooleanLight(
				vehicleConfig.rearLeftTurnLight.outputPin,
				leftTurnIndicatorState,
				brightnessAdjust.getBrightnessLevel(LightType::REAR_LEFT_TURN)
			);
			setBooleanLight(
				vehicleConfig.rearRightTurnLight.outputPin,
				rightTurnIndicatorState,
				brightnessAdjust.getBrightnessLevel(LightType::REAR_RIGHT_TURN)
			);
			setBooleanLight(
				vehicleConfig.brakeLight.outputPin,
				brakeLightState,
				brightnessAdjust.getBrightnessLevel(LightType::BRAKE, LightModes::PRIMARY)
			);
			break;
		case CountryOption::US:
			if (isLeftTurnIndicatorActive || isHazardActive) {
				setBooleanLight(
					vehicleConfig.rearLeftTurnLight.outputPin,
					leftTurnIndicatorState, 
					brightnessAdjust.getBrightnessLevel(LightType::REAR_LEFT_TURN)
				);
			} else if (leftTurnIndicatorState == false) {
				setBrakingWithPark(
					vehicleConfig.rearLeftTurnLight.outputPin,
					parkLightState, 
					brakeLightState,
					brightnessAdjust.getBrightnessLevel(LightType::REAR_LEFT_TURN, LightModes::SECONDARY),
					brightnessAdjust.getBrightnessLevel(LightType::REAR_LEFT_TURN, LightModes::PRIMARY)
				);
			}

			if (isRightTurnIndicatorActive || isHazardActive) {
				setBooleanLight(
					vehicleConfig.rearRightTurnLight.outputPin,
					rightTurnIndicatorState,
					brightnessAdjust.getBrightnessLevel(LightType::REAR_RIGHT_TURN)
				);
			} else if (rightTurnIndicatorState == false) {
				setBrakingWithPark(
					vehicleConfig.rearRightTurnLight.outputPin,
					parkLightState,
					brakeLightState,
					brightnessAdjust.getBrightnessLevel(LightType::REAR_RIGHT_TURN, LightModes::SECONDARY),
					brightnessAdjust.getBrightnessLevel(LightType::REAR_RIGHT_TURN, LightModes::PRIMARY)
				);
			}

			setBrakingWithPark(
				vehicleConfig.brakeLight.outputPin,
				parkLightState,
				brakeLightState,
				brightnessAdjust.getBrightnessLevel(LightType::BRAKE, LightModes::SECONDARY),
				brightnessAdjust.getBrightnessLevel(LightType::BRAKE, LightModes::PRIMARY)
			);
			break;
	};

	/*
	 * Update the debug information
	 */

	if (DEBUGLEVEL >= 1) {
		digitalWrite(vehicleConfig.generalConfig.statusLightPin, controllerStatus(errorFlag));
	}

	if (DEBUGLEVEL >= 2) {
		// Print debug information
		SerialUSB.begin(9600);  // start Serial for Monitoring
	}

	switch (DEBUGLEVEL) {
		case DebugLevel::NONE:
			// No debug information
			break;
		case DebugLevel::STATUS_ONLY:
			// Only show status information
			break;
		case DebugLevel::FUNCTION_STATE:
			if((millis()%1000 >= 500) && (serialIsSent[0] == false)) {
				SerialUSB.print("Function States:\n");
				SerialUSB.print("  - Left Turn Indicator: ");
				SerialUSB.println(leftTurnIndicatorState ? "ON" : "OFF");
				SerialUSB.print("  - Right Turn Indicator: ");
				SerialUSB.println(rightTurnIndicatorState ? "ON" : "OFF");
				SerialUSB.print("  - Brake Light: ");
				SerialUSB.println(brakeLightState ? "ON" : "OFF");
				SerialUSB.print("  - Reverse Light: ");
				SerialUSB.println(reverseLightState ? "ON" : "OFF");
				SerialUSB.print("  - Aux Light: ");
				SerialUSB.println(auxLightState ? "ON" : "OFF");
				SerialUSB.print("  - Parking Light: ");
				SerialUSB.println(parkLightState ? "ON" : "OFF");
				SerialUSB.print("  - Beacon Light State: ");
				SerialUSB.println(beaconLightState ? "ON" : "OFF");
				SerialUSB.print("  - Starter Active: ");
				SerialUSB.println(isStarterActive ? "ON" : "OFF");
				SerialUSB.print("  - Servo Channel 1: ");
				SerialUSB.println(servoChannel1Position);
				SerialUSB.print("  - Servo Output 1: ");
				SerialUSB.println(servoChannel1.read());
				SerialUSB.print("  - Servo Channel 2: ");
				SerialUSB.println(servoChannel2Position);
				SerialUSB.print("  - Servo Output 2: ");
				SerialUSB.println(servoChannel2.read());
				SerialUSB.print("  - Connection Status: ");
				SerialUSB.println(truckSerial.getConnectionStatus() ? "OK" : "ERROR");
				serialIsSent[0] = true;
			} else if((millis()%1000 < 500) && (serialIsSent[0] == true)) {
				serialIsSent[0] = false;
			}
			break;
	};
}

bool controllerStatus(bool errorFlag) {
	if(errorFlag) {
		return true;
	} else {
		uint32_t currentMillis = millis();
		if (currentMillis - StatusPreviousMillis >= 1000) { //Zeitverzoegerte Abfrage
		StatusPreviousMillis = currentMillis;
		pulseStatus = !pulseStatus;
	} else if (currentMillis < StatusPreviousMillis) {  //Reset
		StatusPreviousMillis = currentMillis; 
	}
		return pulseStatus;                 //Flash if everything is OK
	}
}
