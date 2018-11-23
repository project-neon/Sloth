#include <Arduino.h>
#include "_config.h"
#include "Motor.h"

//#include "PID.h"
#include "Encoder.h"
//#include "QTR/QTRSensors.h"



//#define LED  PB1
#define LED(x)  digitalWrite(PB1,x)


//Objects
Motor LeftMotor(PIN_M1_PWM, PIN_M1_IN1, PIN_M1_IN2); // Left Motor
Motor RightMotor(PIN_M2_PWM, PIN_M2_IN1, PIN_M2_IN2); // Right Motor

Encoder LeftEncoder(PIN_ENC1_A, PIN_ENC1_B, PULSES_PER_REV, WHEEL_RADIUS);
Encoder RightEncoder(PIN_ENC2_A, PIN_ENC2_B, PULSES_PER_REV, WHEEL_RADIUS);

//unsigned char pinsLineReader[NUM_SENSORS] = {
//  PIN_LR_S1,
//  PIN_LR_S2,
//  PIN_LR_S3,
//  PIN_LR_S4,
//  PIN_LR_S5,
//  PIN_LR_S6,
//  PIN_LR_S7,
//  PIN_LR_S8
//  };
//
//QTRSensorsAnalog LineReader(pinsLineReader, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
//

//TEST ENCODER

bool AUTO = false; //change here to do test with your hands

void testEncoder(){

    LOG.println("Starting Test Encoder");
    delay(500);

    while(!AUTO){
        LOG.print("Left: ");
        LOG.print("\t");
        LOG.print(LeftEncoder.getPulses());
        LOG.print("\t");
        LOG.print("Right: ");
        LOG.print("\t");
        LOG.print(RightEncoder.getPulses());
        LOG.println();
        delay(100);
    }
    while(AUTO){
        LOG.print("Left: ");
        LOG.print("\t");
        LeftMotor.speed(10);
        delay(250);
        int leftPulses = LeftEncoder.getPulses();
        LOG.print(leftPulses);
        if(leftPulses>0)
            LOG.println("\t left working");
        else if(leftPulses<0)
            LOG.println("\t Change Channels");
        else
            LOG.println("\t Fail");
        LeftMotor.brake();

        delay(1000);

        LOG.print("Right: ");
        LOG.print("\t");
        RightMotor.speed(10);
        delay(250);
        int RightPulses = RightEncoder.getPulses();
        LOG.print(RightPulses);
        if(RightPulses>0)
            LOG.println("\t Right working");
        else if(RightPulses<0)
            LOG.println("\t Change Channels");
        else
            LOG.println("\t Fail");
        RightMotor.brake();
    delay(500);
    LOG.println("Done");
    while(1){

    }
    }





}

void setup() {
  // put your setu  p code here, to run once:
  PC.begin(PC_SPEED);
  BT.begin(BT_SPEED);
//  pinMode(PB1, OUTPUT);

//  LED(1);

}

void loop() {
  // put your main code here, to run repeatedly:
//  float pulsesL = LeftEncoder.getPulses();
//  float pulsesR = RightEncoder.getPulses();
//  LOG.println("Hello");
  testEncoder();
}
