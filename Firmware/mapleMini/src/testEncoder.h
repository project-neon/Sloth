
#include "Encoder.h"
#include "_config.h"

Motor LeftMotor(PIN_M1_PWM, PIN_M1_IN1, PIN_M1_IN2); // Left Motor
Motor RightMotor(PIN_M2_PWM, PIN_M2_IN1, PIN_M2_IN2); // Right Motor

Encoder LeftEncoder(PIN_ENC1_A, PIN_ENC1_B, PULSES_PER_REV, WHEEL_RADIUS);
Encoder RightEncoder(PIN_ENC2_A, PIN_ENC2_B, PULSES_PER_REV, WHEEL_RADIUS);

bool AUTO = true; //change here to do test with your hands

void testEncoder(){

    LOG.println("Starting Test Encoder");
    delay(500);

    if(!AUTO){
        LOG.print("Left: ");
        LOG.print("\t");
        LOG.print(LeftEncoder.getPulses());
        LOG.print("\t");
        LOG.print("Right: ");
        LOG.print("\t");
        LOG.print(RightEncoder.getPulses());
        LOG.println();
    }
    else{
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
    }

    delay(500);
    LOG.println("Done");

    while(1){

    }

}