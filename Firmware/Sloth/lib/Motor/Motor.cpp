#include "Motor.h"

Motor::Motor(PinName pwm, PinName in1, PinName in2):
        _pwm(pwm), _in1(in1), _in2(in2)  {
    _pwm.period(0.00001); //001
    _pwm = 0;
}

void Motor::speed(float speed) {
    _pwm = speed > 0 ? speed : -speed;
    _in1 = (speed >=  0 ? 1 : 0);
    _in2 = (speed >   0 ? 0 : 1);
}

void Motor::coast() {
    _in1 = 0;
    _in2 = 0;
}

void Motor::brake() {
    _in1 = 1;
    _in2 = 1;
}
