# 1 "/home/magraina/projects/trailerLightAndFunction/trailerLightAndFunction.ino"
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
# 25 "/home/magraina/projects/trailerLightAndFunction/trailerLightAndFunction.ino" 2
# 26 "/home/magraina/projects/trailerLightAndFunction/trailerLightAndFunction.ino" 2

/************************************
 * Include Files
 ************************************/




/************************************
 * Definition and Initialisation 
 * Global Vars, Classes and Functions
 ************************************/
//Setup Serial and check if Board is UNO with one Serial or Leonardo/Micro with to Serials
# 52 "/home/magraina/projects/trailerLightAndFunction/trailerLightAndFunction.ino"
bool pulseStatus = false;
uint32_t StatusPreviousMillis = 0;
uint32_t blinkOnTime = 0;

//Functions
bool controllerStatus(bool);
uint8_t blink(uint16_t);


void setup() {
 // put your setup code here, to run once:

 Serial1 /*then define hardware port*/.begin(115200); // start Serial for Communication

 // TODO: Setup IO pins
}

void loop() { // put your main code here, to run repeatedly:
 bool errorFlag = false; // local var for error status


 // Example For later Communication with other Module
 // TODO: Setup Communication


 controllerStatus(errorFlag);
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

uint8_t blink(uint16_t blinkTimeMillis) {
 if((blinkOnTime == 0) || (blinkOnTime > millis())){ //Reset blinkOnTime on startup and on overflow.
  blinkOnTime = millis();
 }
  uint32_t blinkTime = millis() - blinkOnTime;
  if(blinkTime%blinkTimeMillis >= blinkTimeMillis/2){ //ON/OFF Interval at half of Time.
  return 0;
 } else {
  return 1;
 }

}
