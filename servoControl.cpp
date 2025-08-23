#include "servoControl.h"

void Servo::attach(uint8_t pin, uint16_t minMicroseconds, uint16_t maxMicroseconds, uint16_t threshold) {
  if(pin < 9 || pin > 10) return; // Only pins 9 and 10 are supported

  _attachedServo[10 - pin] = pin;
  _minMicroseconds[10 - pin] = minMicroseconds;
  _maxMicroseconds[10 - pin] = maxMicroseconds;
  _currentMicroseconds[10 - pin] = minMicroseconds;
  _threshold = threshold;

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
};

void Servo::detach(uint8_t pin) {
  if(pin < 9 || pin > 10) return; // Only pins 9 and 10 are supported

  _attachedServo[10 - pin] = 0;
  _minMicroseconds[10 - pin] = 0;
  _maxMicroseconds[10 - pin] = 0;
  _currentMicroseconds[10 - pin] = 0;

  if(pin == 9) {
    TCCR1A &= ~(1 << COM1A1); // Disable PWM for Pin 9
  } else if(pin == 10) {
    TCCR1A &= ~(1 << COM1B1); // Disable PWM for Pin 10
  }

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
};

bool Servo::isAttached(uint8_t pin) {
  if(pin < 9 || pin > 10) return false; // Only pins 9 and 10 are supported

  return _attachedServo[10 - pin] != 0;
};

void Servo::writeMicroseconds(uint16_t microSeconds, uint8_t pin) {
  if(pin < 9 || pin > 10) return; // Only pins 9 and 10 are supported

  if(!isAttached(pin)) return; // Servo not attached

  uint16_t minMicroseconds = _minMicroseconds[10 - pin];
  uint16_t maxMicroseconds = _maxMicroseconds[10 - pin];

  if(microSeconds < minMicroseconds) {
    microSeconds = minMicroseconds;
  } else if(microSeconds > maxMicroseconds) {
    microSeconds = maxMicroseconds;
  }

  if(abs((microSeconds - _currentMicroseconds[10 - pin]) < _threshold ) || abs(_currentMicroseconds[10 - pin] - microSeconds) < _threshold) {
    return; // Change is below threshold, do nothing
  }

  _currentMicroseconds[10 - pin] = microSeconds;

  long pulse_ticks = map(microSeconds, 1000, 2000, 2000, 4000);

  if (pin == 9) {
    OCR1A = pulse_ticks;
  } else if (pin == 10) {
    OCR1B = pulse_ticks;
  }
}

// --- Custom Hardware Servo Controller for Arduino Micro (ATmega32U4) ---
//     Uses Timer1 to generate hardware PWM signals on Pins 9 (OC1A) and 10 (OC1B).

// This function configures Timer1 for 50Hz PWM. Call this once in setup().
/* void setupHardwareServo() {
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
} */