#include <Arduino.h>
#include "_config.h"
#include "Motor.h"

#include "PID.h"
#include "Encoder.h"
#include "QTR/QTRSensors.h"



//#define LED	PB1
#define LED(x)	digitalWrite(PB1,x)


//Objects
Motor LeftMotor(PIN_M1_PWM, PIN_M1_IN1, PIN_M1_IN2); // Left Motor
Motor RightMotor(PIN_M2_PWM, PIN_M2_IN1, PIN_M2_IN2); // Right Motor

Encoder LeftEncoder(PIN_ENC1_A, PIN_ENC1_B, PULSES_PER_REV, WHEEL_RADIUS);
Encoder RightEncoder(PIN_ENC2_A, PIN_ENC2_B, PULSES_PER_REV, WHEEL_RADIUS);

unsigned char pinsLineReader[NUM_SENSORS] = {
	PIN_LR_S1, 
	PIN_LR_S2, 
	PIN_LR_S3, 
	PIN_LR_S4, 
	PIN_LR_S5, 
	PIN_LR_S6, 
	PIN_LR_S7, 
	PIN_LR_S8
  };


QTRSensorsAnalog LineReader(pinsLineReader, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
//


void setup() {
  // put your setu	p code here, to run once:
	PC.begin(PC_SPEED);
	BT.begin(BT_SPEED);
//	pinMode(PB1, OUTPUT);
	
//	LED(1);

}

void loop() {
  // put your main code here, to run repeatedly:
//	float pulsesL = LeftEncoder.getPulses();
//	float pulsesR = RightEncoder.getPulses();
	
//	testEncoder();
}