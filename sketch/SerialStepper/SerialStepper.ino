#include <AccelStepper.h>
#include <MultiStepper.h>
#include "pins.h"

AccelStepper steppers[6] = {
	AccelStepper(AccelStepper::DRIVER, StepPin1, DirPin1),
	AccelStepper(AccelStepper::DRIVER, StepPin2, DirPin2),
	AccelStepper(AccelStepper::DRIVER, StepPin3, DirPin3),
	AccelStepper(AccelStepper::DRIVER, StepPin4, DirPin4),
	AccelStepper(AccelStepper::DRIVER, StepPin5, DirPin5),
	AccelStepper(AccelStepper::DRIVER, StepPin6, DirPin6)
};

long steps[6] = {0, 0, 0, 0, 0, 0};


void setup() {
	// put your setup code here, to run once:

	Serial.begin(115200);

	for (byte i = 0; i < 6; i++) {
		steppers[i].setMaxSpeed(100.0);
    	steppers[i].setAcceleration(100.0);
	}
	
}

void loop() {
  // put your main code here, to run repeatedly:
	if(Serial.available() > 1) {
		
		int stepperNumber = Serial.parseInt() - 1;

		if (stepperNumber < 0 || stepperNumber > 5) {
			Serial.print(F("Wrong stepper number: "));
			Serial.println(stepperNumber);
			while (Serial.available()) Serial.read();
		}
		else {
		
			steps[stepperNumber] += Serial.parseInt();

			Serial.print("N. ");
			Serial.print(stepperNumber + 1);
			Serial.print(" S. ");
			Serial.println(steps[stepperNumber]);
		
			steppers[stepperNumber].runToNewPosition(steps[stepperNumber]);
			Serial.println("OK");
		}
	}
}
