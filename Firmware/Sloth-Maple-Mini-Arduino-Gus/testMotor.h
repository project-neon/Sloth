
#include "Motor.h"
#include "_config.h"

Motor LeftMotor(PIN_M1_PWM, PIN_M1_IN1, PIN_M1_IN2); // Left Motor
Motor RightMotor(PIN_M2_PWM, PIN_M2_IN1, PIN_M2_IN2); // Right Motor

void setup(){
  PC.begin(PC_SPEED);
  BT.begin(BT_SPEED);
  LOG.println("Starting Test Motor");

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

void loop(){
  delay(2000);
  testMotor();
}
