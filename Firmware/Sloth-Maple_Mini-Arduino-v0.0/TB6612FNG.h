#include <arduino.h>
#ifndef TB6612FNG_h
#define TB6612FNG_h


class TB6612FNG {
    public:
        TB6612FNG(uint8_t pin_pwm, uint8_t pin_in1, uint8_t pin_in2);
        void pwm(char pwm);
        void coast();
        void brake();
    protected:
        uint8_t _pin_pwm;
        uint8_t _pin_in1;
        uint8_t _pin_in2;
};

#endif
