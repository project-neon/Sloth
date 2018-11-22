#include <Arduino.h>
#include "_config.h"
#include "Motor.h"

//#include "PID.h"
#include "Encoder.h"
//#include "QTRSensors.h"


//Defines


//#define LED	PB1
#define LED(x)	digitalWrite(PB1,x)


//Objects
Motor LeftMotor(PIN_M1_PWM, PIN_M1_IN1, PIN_M1_IN2); // Left Motor
Motor RightMotor(PIN_M2_PWM, PIN_M2_IN1, PIN_M2_IN2); // Right Motor

Encoder LeftEncoder(PIN_ENC1_A, PIN_ENC1_B, PULSES_PER_REV, WHEEL_RADIUS);
Encoder RightEncoder(PIN_ENC2_A, PIN_ENC2_B, PULSES_PER_REV, WHEEL_RADIUS);



//Variables

void setup() {
  // put your setu	p code here, to run once:
	PC.begin(PC_SPEED);
	BT.begin(BT_SPEED);
	pinMode(PB1, OUTPUT);
	
//	LED(1);

}

void loop() {
  // put your main code here, to run repeatedly:
	
	float pulsesL = LeftEncoder.getPulses();
	float pulsesR = RightEncoder.getPulses();
}