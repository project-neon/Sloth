//this class will have the motors configuration, monitoration and control
#include "mbed.h"

#include "_config.h"
#include "_types.h"

//#include "robot.h"

#ifndef MOTORS_H
#define MOTORS_H

// Average of both motors
    PwmOut pwmM1(PIN_M1_EN);
    PwmOut pwmM2(PIN_M2_EN);

    DigitalOut in1M1(PIN_M1_IN1);
    DigitalOut in2M1(PIN_M1_IN2);
    DigitalOut in1M2(PIN_M2_IN1);
    DigitalOut in2M2(PIN_M2_IN2);

class Motors{
public:

    // Initialize pins
    static void init();

    // Set power of both DC motors
    static void setPower(float m1, float m2);

    // Set state as Iddle (Turn off motors)
    static void stop();
};

#endif
