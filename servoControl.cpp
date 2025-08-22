#include "servoControl.h"

uint32_t convertRange(uint32_t signal, uint32_t inMin, uint32_t inMax, uint32_t outMin, uint32_t outMax) {
	uint32_t dynResult;
	if(inMin != inMax) {						//if Min and Max are equal abbort calculation cause of divide by zero
		dynResult = (signal - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
		if(signal > inMax) dynResult = outMax;
		if(signal < inMin) dynResult = outMin;
		return dynResult; 
	} else {
		return 0;
	}
}

void controlServo(bool connectionStatus, Servo& servo, uint16_t position, uint8_t outputPin, uint16_t minMicroseconds, uint16_t maxMicroseconds) {
	// Cut of the last digit to reduce noise
	uint16_t servoMicroseconds = position;

	if(servoMicroseconds < minMicroseconds) {
		servoMicroseconds = minMicroseconds;
	} else if(servoMicroseconds > maxMicroseconds) {
		servoMicroseconds = maxMicroseconds;
	}

	if (connectionStatus) {
		if(!servo.attached()) servo.attach(outputPin);
		servo.writeMicroseconds(servoMicroseconds);
	} else {
		if(servo.attached()) servo.detach();
	}
}

void positionServo(bool connectionStatus, Servo& servo, bool isUp, bool isDown, uint8_t outputPin, uint16_t minMicroseconds, uint16_t maxMicroseconds) {
	if(isUp && !isDown) {
		controlServo(connectionStatus, servo, maxMicroseconds, outputPin, minMicroseconds, maxMicroseconds);
	} else if(!isUp && isDown) {
		controlServo(connectionStatus, servo, minMicroseconds, outputPin, minMicroseconds, maxMicroseconds);
	} else if(isUp && isDown) {
		controlServo(connectionStatus, servo, 1520, outputPin, minMicroseconds, maxMicroseconds);
	} else {
		if(servo.attached()) servo.detach();
	}
}