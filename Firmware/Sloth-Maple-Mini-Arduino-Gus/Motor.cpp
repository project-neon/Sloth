#include "Motor.h"

HardwareTimer timer(1);

Motor::Motor(uint8_t pinPwm, uint8_t in1, uint8_t in2)
{
	_in1 = in1;
	_in2 = in2;
	_pinPwm = pinPwm;
	// Setup the PWM frequency to ~95kHz (Timer One)
  	timer.setPrescaleFactor(1);
  	timer.setOverflow(760);

	pinMode(_pinPwm, PWM);
	pinMode(_in1, OUTPUT);
	pinMode(_in2, OUTPUT);

	//Start in zero
	pwmWrite(_pinPwm, 0);
	digitalWrite(_in1, 0);
	digitalWrite(_in2, 0);
}

void Motor::speed(int speed) {
	int power = speed > 0 ? speed : -speed;
	pwmWrite(_pinPwm, map(power, 0, 100, 0, 761));
	digitalWrite(_in1, speed >=  0 ? HIGH : LOW);
  digitalWrite(_in2, speed >   0 ? LOW : HIGH);
}

void Motor::coast() {
	digitalWrite(_in1, 0);
	digitalWrite(_in2, 0);
}

void Motor::brake() {
	digitalWrite(_in1, 1);
	digitalWrite(_in2, 1);
}
