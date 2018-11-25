#include <Arduino.h>
#ifndef Motor_h
#define Motor_h


class Motor {
    public:
        Motor(uint8_t pinPwm, uint8_t in1, uint8_t in2);
        void speed(float speed);
        void coast();
        void brake();
    protected:
        uint8_t _pinPwm;
        uint8_t _in1;
        uint8_t _in2;
};

#endif
