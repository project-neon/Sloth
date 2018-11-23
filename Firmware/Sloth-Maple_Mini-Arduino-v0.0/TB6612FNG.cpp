#include "TB6612FNG.h"

HardwareTimer timer(1);

TB6612FNG::TB6612FNG(uint8_t pin_pwm, uint8_t pin_in1, uint8_t pin_in2)
{
	_pin_pwm = pin_pwm;
	_pin_in1 = pin_in1;
	_pin_in2 = pin_in2;

	// Setup the PWM frequency to ~95kHz (Timer One)
	timer.setPrescaleFactor(1);
	timer.setOverflow(760);

	pinMode(_pin_pwm, PWM);
	pinMode(_pin_in1, OUTPUT);
	pinMode(_pin_in2, OUTPUT);

	//Start in zero
	pwmWrite(_pin_pwm, 0);
	digitalWrite(_pin_in1, 0);
	digitalWrite(_pin_in2, 0);
}

void TB6612FNG::pwm(float pwm) {
	float power = pwm > 0.0 ? pwm : -pwm;
	pwmWrite(_pin_pwm, (int) (power * 761.0));
	digitalWrite(_pin_in1, pwm >=  0.0 ? 1 : 0);
  digitalWrite(_pin_in2, pwm >   0.0 ? 0 : 1);
}

void TB6612FNG::coast() {
	pwmWrite(_pin_pwm, 0);
	digitalWrite(_pin_in1, 0);
	digitalWrite(_pin_in2, 0);
}

void TB6612FNG::brake() {
	pwmWrite(_pin_pwm, 0);
	digitalWrite(_pin_in1, 1);
	digitalWrite(_pin_in2, 1);
}
