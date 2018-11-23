#include <arduino.h>
#ifndef TB6612FNG_h
#define TB6612FNG_h


class TB6612FNG {
    public:
        TB6612FNG(uint8_t pinPwm, uint8_t in1, uint8_t in2);
        void pwm(char pwm);
        void coast();
        void brake();
    protected:
        uint8_t _pinPwm;
        uint8_t _in1;
        uint8_t _in2;
};

#endif
