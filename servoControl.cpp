#include "servoControl.h"


// --- Custom Hardware Servo Controller for Arduino Micro (ATmega32U4) ---
//     Uses Timer1 to generate hardware PWM signals on Pins 9 (OC1A) and 10 (OC1B).

// This function configures Timer1 for 50Hz PWM. Call this once in setup().
void setupHardwareServo() {
  // 1. Set the PWM pins (Pin 9 and 10) as outputs
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // 2. Configure Timer1 for Fast PWM mode (Mode 14)
  //    This mode uses ICR1 to define the frequency (the "TOP" value)
  TCCR1A = 0; // Clear control registers
  TCCR1B = 0;
  
  // Set output compare modes for Pin 9 and 10 to non-inverting PWM
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1); 
  
  // Set WGM bits for Mode 14
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);

  // 3. Set the frequency to 50 Hz.
  //    Formula: F_CPU / (Prescaler * (ICR1 + 1)) = Frequency
  //    16,000,000 / (8 * (39999 + 1)) = 50 Hz
  TCCR1B |= (1 << CS11);  // Set prescaler to 8
  ICR1 = 39999;           // Set TOP value for 50 Hz period
}

// This function maps an angle (0-180) to a pulse width and sets the servo position.
void writeHardwareServo(int microSeconds, int pin, uint16_t minMicroseconds, uint16_t maxMicroseconds) {
  // The timer has 40,000 "ticks" over the 20ms period.
  // 1ms pulse (0 deg)   = (1ms / 20ms) * 40000 = 2000 ticks.
  // 2ms pulse (180 deg) = (2ms / 20ms) * 40000 = 4000 ticks.

  uint16_t servoMicroseconds = microSeconds;

  if(servoMicroseconds < minMicroseconds) {
		servoMicroseconds = minMicroseconds;
	} else if(servoMicroseconds > maxMicroseconds) {
		servoMicroseconds = maxMicroseconds;
	}
  
  long pulse_ticks = map(servoMicroseconds, 1000, 2000, 2000, 4000);

  // Set the correct output compare register based on the pin number
  if (pin == 9) {
    OCR1A = pulse_ticks;
  } else if (pin == 10) {
    OCR1B = pulse_ticks;
  }
}