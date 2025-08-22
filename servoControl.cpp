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
	uint16_t servoMicroseconds = convertRange(
		position,
		0, 1023, // Input range for angle
		1020, 1980 // Output range for microseconds
	);

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