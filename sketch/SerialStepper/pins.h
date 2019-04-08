/* 
 * This file is part of the RoboVintage https://github.com/FabLabAQ/RoboVintage.
 * Copyright (c) 2019 FabLabAQ <info@fablaquila.org>.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PINS_H
#define PINS_H

/*
 * Shield configuration (view from top):
 * 
 *  -----------------------------
 * |     stepsticks      | power |
 * |---------------------|-------|
 * | 4:       | 1:       |  12V  |
 * |   stp 12 |   stp 11 |  GND  |
 * |   dir 13 |   dir 10 |-------
 * |----------|----------|
 * | 5:       | 2:       |
 * |   stp  8 |   stp  7 |
 * |   dir  9 |   dir  6 |
 * |----------|----------|
 * | 6:       | 3:       |
 * |   stp  4 |   stp  3 |
 * |   dir  5 |   dir  2 |
 * |---------------------|
 * |endstops/gen. purpose|
 * |---------------------|
 * |GND GND GND A4 GND 5V|
 * |A0  A1  A2  A3 GND 5V|
 *  ---------------------
 *  
 *  Motor description:
 *  1: Base joint
 *  2: Near arm joint
 *  3: Far arm joint
 *  4: Left gripper joint
 *  5: Gripper
 *  6: Right gripper joint
 *  
 *  Endstop description:
 *  A0: Gripper
 *  A1: Near arm
 *  A2: Far arm
 *  A4: Base
 *  A3: spare
 *  
 *  Steppers enable: A5
 *  
 */

const uint8_t
	DirPin1 = 10,
	StepPin1 = 11,
	DirPin2 = 6,
	StepPin2 = 7,
	DirPin3 = 2,
	StepPin3 = 3,
	DirPin4 = 13,
	StepPin4 = 12,
	DirPin5 = 9,
	StepPin5 = 8,
	DirPin6 = 5,
	StepPin6 = 4,
	EnPin = A5,
	EndPin1 = A4,
	EndPin2 = A1,
	EndPin3 = A2,
	EndPin4 = A3,
	EndPin5 = A0;

#define DIR_DELAY 1
#define STEP_DELAY 2

#define DELAY_CYCLES(n) __builtin_avr_delay_cycles(n)

#define	 DIR_PIN_1 PB2
#define	STEP_PIN_1 PB3
#define	 DIR_PIN_2 PD6
#define	STEP_PIN_2 PD7
#define	 DIR_PIN_3 PD2
#define	STEP_PIN_3 PD3
#define	 DIR_PIN_4 PB5
#define	STEP_PIN_4 PB4
#define	 DIR_PIN_5 PB1
#define	STEP_PIN_5 PB0
#define	 DIR_PIN_6 PD5
#define	STEP_PIN_6 PD4

const int stepRad[] = {
	480,
	480,
	500,
	600
};

const float limits[][2] = {
	{-2.618, 2.618},
	{-2.356, 0.785},
	{-2.356, -0.09},
	{-1.57, 1.57},
	{0, 95}
};

const float ArmJointComp = 2.0;

void EnableSteppers() {
	PORTC = 0x1F;
}

void DisableSteppers() {
	PORTC = 0x3F;
}

void PinSetup() {
	/*
	pinMode(EnPin, OUTPUT);
	digitalWrite(EnPin, HIGH);
	pinMode(EndPin1, INPUT_PULLUP);
	pinMode(EndPin2, INPUT_PULLUP);
	pinMode(EndPin3, INPUT_PULLUP);
	pinMode(EndPin4, INPUT_PULLUP);
	pinMode(EndPin5, INPUT_PULLUP);
	*/
	// equivalent to:
	PORTC = 0x3F;
	DDRC = _BV(PC5);
	
	// the following is equivalent to
	// pinMode(every DirPinX/StepPinY, OUTPUT)
	DDRB = 0x3F;
	DDRD = 0xFC;
}

inline void forward1 () {
	PORTB |= _BV(DIR_PIN_1);
	DELAY_CYCLES(DIR_DELAY);
	PORTB |= _BV(STEP_PIN_1);
	DELAY_CYCLES(STEP_DELAY);
	PORTB &= ~_BV(STEP_PIN_1);
}

inline void backward1 () {
	PORTB &= ~_BV(DIR_PIN_1);
	DELAY_CYCLES(DIR_DELAY);
	PORTB |= _BV(STEP_PIN_1);
	DELAY_CYCLES(STEP_DELAY);
	PORTB &= ~_BV(STEP_PIN_1);
}

inline void forward4 () {
	PORTB |= _BV(DIR_PIN_4);
	DELAY_CYCLES(DIR_DELAY);
	PORTB |= _BV(STEP_PIN_4);
	DELAY_CYCLES(STEP_DELAY);
	PORTB &= ~_BV(STEP_PIN_4);
}

inline void backward4 () {
	PORTB &= ~_BV(DIR_PIN_4);
	DELAY_CYCLES(DIR_DELAY);
	PORTB |= _BV(STEP_PIN_4);
	DELAY_CYCLES(STEP_DELAY);
	PORTB &= ~_BV(STEP_PIN_4);
}

inline void forward5 () {
	PORTB |= _BV(DIR_PIN_5);
	DELAY_CYCLES(DIR_DELAY);
	PORTB |= _BV(STEP_PIN_5);
	DELAY_CYCLES(STEP_DELAY);
	PORTB &= ~_BV(STEP_PIN_5);
}

inline void backward5 () {
	PORTB &= ~_BV(DIR_PIN_5);
	DELAY_CYCLES(DIR_DELAY);
	PORTB |= _BV(STEP_PIN_5);
	DELAY_CYCLES(STEP_DELAY);
	PORTB &= ~_BV(STEP_PIN_5);
}

inline void forward2 () {
	PORTD |= _BV(DIR_PIN_2);
	DELAY_CYCLES(DIR_DELAY);
	PORTD |= _BV(STEP_PIN_2);
	DELAY_CYCLES(STEP_DELAY);
	PORTD &= ~_BV(STEP_PIN_2);
}

inline void backward2 () {
	PORTD &= ~_BV(DIR_PIN_2);
	DELAY_CYCLES(DIR_DELAY);
	PORTD |= _BV(STEP_PIN_2);
	DELAY_CYCLES(STEP_DELAY);
	PORTD &= ~_BV(STEP_PIN_2);
}

inline void forward3 () {
	PORTD |= _BV(DIR_PIN_3);
	DELAY_CYCLES(DIR_DELAY);
	PORTD |= _BV(STEP_PIN_3);
	DELAY_CYCLES(STEP_DELAY);
	PORTD &= ~_BV(STEP_PIN_3);
}

inline void backward3 () {
	PORTD &= ~_BV(DIR_PIN_3);
	DELAY_CYCLES(DIR_DELAY);
	PORTD |= _BV(STEP_PIN_3);
	DELAY_CYCLES(STEP_DELAY);
	PORTD &= ~_BV(STEP_PIN_3);
}

inline void forward6 () {
	PORTD |= _BV(DIR_PIN_6);
	DELAY_CYCLES(DIR_DELAY);
	PORTD |= _BV(STEP_PIN_6);
	DELAY_CYCLES(STEP_DELAY);
	PORTD &= ~_BV(STEP_PIN_6);
}

inline void backward6 () {
	PORTD &= ~_BV(DIR_PIN_6);
	DELAY_CYCLES(DIR_DELAY);
	PORTD |= _BV(STEP_PIN_6);
	DELAY_CYCLES(STEP_DELAY);
	PORTD &= ~_BV(STEP_PIN_6);
}



#endif // PINS_H
