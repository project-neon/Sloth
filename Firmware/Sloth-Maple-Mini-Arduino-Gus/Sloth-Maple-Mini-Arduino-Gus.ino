
#include "Motor.h"
// #include "Encoder.h"
#include "_config.h"
#include "QEI.h"

Motor LeftMotor(PIN_M1_PWM, PIN_M1_IN1, PIN_M1_IN2);
Motor RightMotor(PIN_M2_PWM, PIN_M2_IN1, PIN_M2_IN2);

QEI LeftEncoder(PIN_ENC1_A, PIN_ENC1_B, PULSES_PER_REV, WHEEL_RADIUS);
QEI RightEncoder(PIN_ENC2_A, PIN_ENC2_B, PULSES_PER_REV, WHEEL_RADIUS);

void setup(){
  PC.begin(PC_SPEED);
  BT.begin(BT_SPEED);
  LOG.println("Starting Test Motor");
  setupLeftEncoder();
  setupRightEncoder();
}


void testMotor(){

    LOG.println("Test Left in 25%");
    LeftMotor.speed(25);
    delay(1000);
    LOG.println("Test Left in 50%");
    LeftMotor.speed(50);
    delay(1000);
    LOG.println("Test Left in 100%");
    LeftMotor.speed(100);
    delay(1000);
    LOG.println("Coast Left");
    LeftMotor.coast();
    delay(1000);
    LOG.println("Brake Left");
    LeftMotor.brake();
    delay(1000);
    LOG.println("Test reverse Left in -25%");
    LeftMotor.speed(-25);
    delay(1000);
    LOG.println("Test reverse Left in -50%");
    LeftMotor.speed(-50);
    delay(1000);
    LOG.println("Coast Left");
    LeftMotor.coast();
    delay(1000);
    LOG.println("Brake Left");
    LeftMotor.brake();
    delay(1000);

    LOG.println("Test Right in 25%");
    RightMotor.speed(25);
    delay(1000);
    LOG.println("Test Right in 50%");
    RightMotor.speed(50);
    delay(1000);
    LOG.println("Test Right in 100%");
    RightMotor.speed(100);
    delay(1000);
    LOG.println("Coast Right");
    RightMotor.coast();
    delay(1000);
    LOG.println("Brake Right");
    RightMotor.brake();
    delay(1000);
    LOG.println("Test reverse Right in -25%");
    RightMotor.speed(-25);
    delay(1000);
    LOG.println("Test reverse Right in -50%");
    RightMotor.speed(-50);
    delay(1000);
    LOG.println("Coast Right");
    RightMotor.coast();
    delay(1000);
    LOG.println("Brake Right");
    RightMotor.brake();
    delay(3000);

}

//TEST ENCODER

bool AUTO_ENCODER = true; //change here to do test with your hands

void leftEncoder() {
  LeftEncoder.encode();
}

void setupLeftEncoder() {
  //X2 encoding uses interrupts on only channel A.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC1_A), leftEncoder, CHANGE);

  //X4 encoding uses interrupts on      channel A,
  //and on channel B.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC1_B), leftEncoder, CHANGE);
}

void rightEncoder() {
  RightEncoder.encode();
}

void setupRightEncoder() {
  //X2 encoding uses interrupts on only channel A.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC2_A), rightEncoder, CHANGE);

  //X4 encoding uses interrupts on      channel A,
  //and on channel B.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC2_B), rightEncoder, CHANGE);
}

void testEncoder(){

    LOG.println("Starting Test Encoder");
    delay(500);

    while(!AUTO_ENCODER){
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
    while(AUTO_ENCODER){
        LOG.print("Left: ");
        LOG.print("\t");
        LeftMotor.speed(25);
        delay(1000);
        int leftPulses = LeftEncoder.getPulses();
        LOG.print(leftPulses);
        if(leftPulses>0)
            LOG.println("\t Left working");
        else if(leftPulses<0)
            LOG.println("\t Change Channels");
        else
            LOG.println("\t Fail");
        LeftMotor.brake();

        delay(1000);

        LOG.print("Right: ");
        LOG.print("\t");
        RightMotor.speed(25);
        delay(1000);
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
    LeftEncoder.reset();
    RightEncoder.reset();
  }
}

void loop(){
  // delay(2000);
  // testMotor();
  testEncoder();
  // testQTR();
  delay(1000);
}
