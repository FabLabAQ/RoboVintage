#ifndef PINS_H
#define PINS_H

/*
 * Shield configuration (view from top):
 * 
 *  -----------------------------
 * |     stepsticks      | power |
 * |---------------------|-------|
 * | 4:       | 1:       |  +12V |
 * |   stp 12 |   stp 11 |  -GND |
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
 * |A0 A1 A2 A3 A4 A5 A6 |
 *  ---------------------
 *  
 *  Motor description:
 *  1: Base joint
 *  2: 
 *  3:
 *  4:
 *  5:
 *  6:
 *  
 *  Endstop description:
 *  A6: gripper
 *  
 */

/*  Steps/deg:
 *  Base joint = 8.333
 *  Lower arm = 8.333
 *  
 *  
 *  Limits:
 *  Base joint = -150/+150
 *  
 *  
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
	StepPin6 = 4;



#endif // PINS_H
