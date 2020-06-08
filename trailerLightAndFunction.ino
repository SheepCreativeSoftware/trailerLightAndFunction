/************************************ 
 * trailerLightAndFunction v0.0.3
 * Date: 08.06.2020 | 18:13
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
#define ContryOption EU                   //Setup Region EU or US for Truck
#define serialCom false                     //Activate Communication to other modules via I2C 
#if (serialCom == true)
	#define truckAdress 1                     	//Serial Adress for Module: Truck
	#define beaconAdress 2                  	//Serial Adress for this Module: Beacon Lights Extension
	#define trailerAdress 3                  	//Serial Adress for Module: Trailer 
	#define extFunctionAdress 4               	//Serial Adress for Module: Special function for example Servos Steering
#endif
//Change this value for different debuging levels
#define debugLevel 3						////1 = Status LED | >2 = Serial Monitor                        
/************************************
 * Include Files
 ************************************/


/************************************
 * Definition IO Pins
 ************************************/
// TODO: setup correct pins
//Pinout Arduino Micro:
//I2C 2+3 | PWM 3, 5, 6, 9, 10, 11, 13 | LED 13
//Servo Lib deactivates PWM functionality on pins 9 and 10

//Inputs
//Nothing

//Outputs
#define outStatusLed 13                   //Arduino status LED output Pin
#define outParkingLight 4                 //Parking light output pin
#define outRearLeftFlashLight 5           //Rear left flashing light output pin | PWM Needed for US
#define outRearRightFlashLight 6          //Rear right flashing light output pin | PWM Needed for US
#define outReverseLight 7                 //Reverse light output pin
#define outBrakeLight 11                  //Brake light output pin | PWM for Parking Light
#define outAuxLight 12                    //Reserved for Special Auxiliary Light
//Free IOs 0, 1, 4, 7, 18, 19

/************************************
 * Definition and Initialisation 
 * Global Vars, Classes and Functions
 ************************************/
// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#if (SERIAL_PORT_MONITOR != SERIAL_PORT_HARDWARE) 	//if serial ports are different then the arduino has more than one serial port
	#ifndef SerialUSB								//if not allready defined
		#define SerialUSB SERIAL_PORT_MONITOR		//then define monitor port
	#endif
#else
	#if (debugLevel >1)								//if serial ports are the same debuging is not possible (for example on UNO)
		#define debugLevel 1						//do not change!!!
	#endif
#endif
#ifndef SerialHW									//if not allready defined
	#define SerialHW SERIAL_PORT_HARDWARE			//then define hardware port
#endif

bool pulseStatus = false;
unsigned long StatusPreviousMillis = 0;
unsigned long blinkOnTime = 0;

//Functions
bool controllerStatus(bool);
int blink(unsigned int);


void setup() {
	// put your setup code here, to run once:
	#if (serialCom == true)
	SerialHW.begin(115200);  // start Serial for Communication
	#endif
	// TODO: Setup IO pins
}

void loop() {                             // put your main code here, to run repeatedly:
	bool errorFlag = false;                 // local var for error status


	// Example For later Communication with other Module
	// TODO: Setup Communication
	

	controllerStatus(errorFlag);
}

bool controllerStatus(bool errorFlag) {
	if(errorFlag) {
		return true;
	} else {
		unsigned long currentMillis = millis();
		if (currentMillis - StatusPreviousMillis >= 1000) { //Zeitverzoegerte Abfrage
		StatusPreviousMillis = currentMillis;
		pulseStatus = !pulseStatus;
	} else if (currentMillis < StatusPreviousMillis) {  //Reset
		StatusPreviousMillis = currentMillis; 
	}
		return pulseStatus;                 //Flash if everything is OK
	}
}

int blink(unsigned int blinkTimeMillis) {
	if((blinkOnTime == 0) || (blinkOnTime > millis())){ //Reset blinkOnTime on startup and on overflow.
		blinkOnTime = millis();
	}
		unsigned long blinkTime = millis() - blinkOnTime;
		if(blinkTime%blinkTimeMillis >= blinkTimeMillis/2){ //ON/OFF Interval at half of Time.
		return 0;
	} else {
		return 1;
	}

}
