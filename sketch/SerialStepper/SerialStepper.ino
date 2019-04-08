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


/* 
 * Example commands:
 * 1 45 2 30 3 -30 4 -30 5 45
 * 1 -45 2 -30 3 30 4 30 5 -45
 * 
 * 
 */

#include <AccelStepper.h>
#include <MultiStepper.h>
#include "pins.h"

MultiStepper multiStepper;

/*
AccelStepper steppers[6] = {
	AccelStepper(AccelStepper::DRIVER, StepPin1, DirPin1),
	AccelStepper(AccelStepper::DRIVER, StepPin2, DirPin2),
	AccelStepper(AccelStepper::DRIVER, StepPin3, DirPin3),
	AccelStepper(AccelStepper::DRIVER, StepPin4, DirPin4),
	AccelStepper(AccelStepper::DRIVER, StepPin5, DirPin5),
	AccelStepper(AccelStepper::DRIVER, StepPin6, DirPin6)
};
*/

AccelStepper steppers[6] = {
	AccelStepper(forward1, backward1),
	AccelStepper(forward2, backward2),
	AccelStepper(forward3, backward3),
	AccelStepper(forward4, backward4),
	AccelStepper(forward5, backward5),
	AccelStepper(forward6, backward6)
};

long steps[6] = {0, 0, 0, 0, 0, 0};

float angles[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

void MoveRelative(float * in, long * out) {
	// base joint
	out[0] = stepRad[0] * in[0];
	// near arm joint
	out[1] = stepRad[1] * in[1];
	// far arm joint
	out[2] = (in[2] + in[1] * 0.5) * stepRad[2];
	// left gripper joint
	out[3] = (in[3] - in[4] + in[1] * 0.5) * stepRad[3];
	// right gripper joint
	out[5] = (-in[3] - in[4] -in[1] * 0.5) * stepRad[3];
	// gripper
	out[4] = in[5] * DEG_TO_RAD*1000;
}

void setup() {
	PinSetup();
	
	Serial.begin(115200);

	for (byte i = 0; i < 6; i++) {
		steppers[i].setMaxSpeed(250.0);
    	//steppers[i].setAcceleration(50.0);
    	multiStepper.addStepper(steppers[i]);
	}
	//steppers[5].setMaxSpeed(100.0);
	
}

void loop() {
  // put your main code here, to run repeatedly:
	if(Serial.available() > 1) {

		do{
		
		int stepperNumber = Serial.parseInt() - 1;

		if (stepperNumber < 0 || stepperNumber > 5) {
			Serial.print(F("Wrong stepper number: "));
			Serial.println(stepperNumber);
			while (Serial.available()) Serial.read();
		}
		else {
		
			angles[stepperNumber] += Serial.parseFloat()*DEG_TO_RAD;

			Serial.print("N. ");
			Serial.print(stepperNumber + 1);
			Serial.print(" S. ");
			Serial.println(angles[stepperNumber]*RAD_TO_DEG);
		}
	} while (Serial.read() != '\n');

			MoveRelative(angles, steps);
			multiStepper.moveTo(steps);
			EnableSteppers();
			multiStepper.runSpeedToPosition();
			DisableSteppers();
			Serial.println("OK");
		
	}
}
