#ifndef Motor_h
#define Motor_h

#include "mbed.h"

class Motor {
    public:
        Motor(PinName pwm, PinName in1, PinName in2);
        void speed(float speed);
        void coast();
        void brake();     
    protected:
    mutable PwmOut _pwm;
    mutable DigitalOut _in1;
    mutable DigitalOut _in2;
};

#endif