#include "TB6612FNG.h"

HardwareTimer timer(1);

TB6612FNG::TB6612FNG(uint8_t pinPwm, uint8_t in1, uint8_t in2)
{
	_in1 = in1;
	_in2 = in2;
	_pinPwm = pinPwm;

	// Setup the PWM frequency to ~95kHz (Timer One)
	timer.setPrescaleFactor(1);
	timer.setOverflow(760);

	pinMode(pinPwm, PWM);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);

	//Start in zero
	pwmWrite(_pinPwm, 0);
	digitalWrite(_in1, 0);
	digitalWrite(_in2, 0);
}

void TB6612FNG::pwm(char pwm) {
	char power = pwm > 0 ? pwm : -pwm;
	pwmWrite(_pinPwm, map(power, 0, 100, 0, 761));

	digitalWrite(_in1, pwm >=  0 ? 1 : 0);
  digitalWrite(_in2, pwm >   0 ? 0 : 1);
}

void TB6612FNG::coast() {
	pwmWrite(_pinPwm, 0);
	digitalWrite(_in1, 0);
	digitalWrite(_in2, 0);
}

void TB6612FNG::brake() {
	pwmWrite(_pinPwm, 0);
	digitalWrite(_in1, 1);
	digitalWrite(_in2, 1);
}
