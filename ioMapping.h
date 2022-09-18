/************************************ 
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

#ifndef _IO_MAPPING_H_
#define _IO_MAPPING_H_

/************************************
 * Definition IO Pins
 ************************************/
// TODO: setup correct pins
//Pinout Arduino Micro:
//I2C 2+3 | PWM 3, 5, 6, 9, 10, 11, 13 | LED 13
//Servo Lib deactivates PWM functionality on pins 9 and 10

//Inputs
// Pin 2+3 reserved for I2C!
#define outTxEnablePin 2

//Outputs
#define outStatusLed 13                   //Arduino status LED output Pin
#define outParkingLight 7                 //Parking light output pin
#define outSideLeftFlashLight 3           //Rear left flashing light output pin | PWM Needed for US
#define outSideRightFlashLight 4          //Rear right flashing light output pin | PWM Needed for US
#define outRearLeftFlashLight 5           //Rear left flashing light output pin | PWM Needed for US
#define outRearRightFlashLight 6          //Rear right flashing light output pin | PWM Needed for US
#define outReverseLight 8                 //Reverse light output pin
#define outBrakeLight 9                  //Brake light output pin | PWM for Parking Light
#define outAuxLight 12                    //Reserved for Special Auxiliary Light
//Free IOs 0, 1, 4, 7, 18, 19

#endif