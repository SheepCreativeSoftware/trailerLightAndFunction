# 1 "/home/magraina/projects/trailerLightAndFunction/trailerLightAndFunction.ino"
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
# 25 "/home/magraina/projects/trailerLightAndFunction/trailerLightAndFunction.ino" 2
# 26 "/home/magraina/projects/trailerLightAndFunction/trailerLightAndFunction.ino" 2

/************************************
 * Include Files
 ************************************/
# 31 "/home/magraina/projects/trailerLightAndFunction/trailerLightAndFunction.ino" 2
# 32 "/home/magraina/projects/trailerLightAndFunction/trailerLightAndFunction.ino" 2

/************************************
 * Definition and Initialisation 
 * Global Vars, Classes and Functions
 ************************************/
//Setup Serial and check if Board is UNO with one Serial or Leonardo/Micro with to Serials
# 51 "/home/magraina/projects/trailerLightAndFunction/trailerLightAndFunction.ino"
bool pulseStatus = false;
uint32_t StatusPreviousMillis = 0;
uint32_t blinkOnTime = 0;

//Functions
bool controllerStatus(bool);
uint8_t blink(uint16_t);


void setup() {

 serialConfigure(&Serial1 /*then define hardware port*/, // Serial interface on arduino
     19200, // Baudrate
     0x06, // e.g. SERIAL_8N1 | start bit, data bit, stop bit
     2 // Pin to switch between Transmit and Receive
 );




 initLightOutput(); // Init SoftPWM Lib
 setupLightOutput(7 /*Parking light output pin*/, 200 /* 200ms Fade on time for the Light*/, 200 /* 200ms Fade off time for the Light*/); // Create and set pin | Set fade up and down time for pin
 setupLightOutput(3 /*Rear left flashing light output pin | PWM Needed for US*/, 200 /* 200ms Fade on time for the Light*/, 200 /* 200ms Fade off time for the Light*/); // Create and set pin | Set fade up and down time for pin
 setupLightOutput(4 /*Rear right flashing light output pin | PWM Needed for US*/, 200 /* 200ms Fade on time for the Light*/, 200 /* 200ms Fade off time for the Light*/); // Create and set pin | Set fade up and down time for pin
 setupLightOutput(5 /*Rear left flashing light output pin | PWM Needed for US*/, 200 /* 200ms Fade on time for the Light*/, 200 /* 200ms Fade off time for the Light*/); // Create and set pin | Set fade up and down time for pin
 setupLightOutput(6 /*Rear right flashing light output pin | PWM Needed for US*/, 200 /* 200ms Fade on time for the Light*/, 200 /* 200ms Fade off time for the Light*/); // Create and set pin | Set fade up and down time for pin
 setupLightOutput(8 /*Reverse light output pin*/, 200 /* 200ms Fade on time for the Light*/, 200 /* 200ms Fade off time for the Light*/); // Create and set pin | Set fade up and down time for pin
 setupLightOutput(11 /*Brake light output pin | PWM for Parking Light*/, 200 /* 200ms Fade on time for the Light*/, 200 /* 200ms Fade off time for the Light*/); // Create and set pin | Set fade up and down time for pin
 setupLightOutput(12 /*Reserved for Special Auxiliary Light*/, 200 /* 200ms Fade on time for the Light*/, 200 /* 200ms Fade off time for the Light*/); // Create and set pin | Set fade up and down time for pin
}

void loop() { // put your main code here, to run repeatedly:
 bool errorFlag = false; // local var for error status


 serialUpdate(); // Update Data from serial communication
 bool parkLightState = getLightData(0); // Get Light State from Serial Interface
 bool brakeLightState = getLightData(1); // Get Light State from Serial Interface
 bool reverseLightState = getLightData(2); // Get Light State from Serial Interface
 bool rightBlinkLightState = getLightData(3); // Get Light State from Serial Interface
 bool leftBlinkLightState = getLightData(4); // Get Light State from Serial Interface
 bool auxLightState = getLightData(5); // Get Light State from Serial Interface
 bool beaconLightState = getLightData(6); // Get Light State from Serial Interface
 bool dimmLightState = getLightData(7); // Get Light State from Serial Interface


 uint8_t normalDimming = starterDimming(dimmLightState, 255, 5 /* Divisor for Dimming function*/, 2 /* 0-255 MAX Value for all light when active starter is activ*/);

 setBooleanLight(7 /*Parking light output pin*/, parkLightState, normalDimming);

 setBooleanLight(5 /*Rear left flashing light output pin | PWM Needed for US*/, leftBlinkLightState, normalDimming);
 setBooleanLight(6 /*Rear right flashing light output pin | PWM Needed for US*/, rightBlinkLightState, normalDimming);


 setBooleanLight(3 /*Rear left flashing light output pin | PWM Needed for US*/, leftBlinkLightState, normalDimming);
 setBooleanLight(4 /*Rear right flashing light output pin | PWM Needed for US*/, rightBlinkLightState, normalDimming);


 // Option for US needed


 uint8_t parkDimming = starterDimming(dimmLightState, 100, 5 /* Divisor for Dimming function*/, 2 /* 0-255 MAX Value for all light when active starter is activ*/);
 setBrakingWithPark(11 /*Brake light output pin | PWM for Parking Light*/, parkLightState, brakeLightState, parkDimming, normalDimming);




 setBooleanLight(8 /*Reverse light output pin*/, reverseLightState, normalDimming);

 setBooleanLight(12 /*Reserved for Special Auxiliary Light*/, auxLightState, normalDimming);


 digitalWrite(13 /*Arduino status LED output Pin*/, controllerStatus(errorFlag));

}

bool controllerStatus(bool errorFlag) {
 if(errorFlag) {
  return true;
 } else {
  uint32_t currentMillis = millis();
  if (currentMillis - StatusPreviousMillis >= 1000) { //Zeitverzoegerte Abfrage
  StatusPreviousMillis = currentMillis;
  pulseStatus = !pulseStatus;
 } else if (currentMillis < StatusPreviousMillis) { //Reset
  StatusPreviousMillis = currentMillis;
 }
  return pulseStatus; //Flash if everything is OK
 }
}
