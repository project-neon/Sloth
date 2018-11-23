#include "TB6612FNG.h"

HardwareTimer timer(1);

TB6612FNG::TB6612FNG(uint8_t pinPwm, uint8_t in1, uint8_t in2)
{
	_pin_in1 = in1;
	_pin_in2 = in2;
	_pin_pwm = pinPwm;

	// Setup the PWM frequency to ~95kHz (Timer One)
	timer.setPrescaleFactor(1);
	timer.setOverflow(760);

	pinMode(pinPwm, PWM);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);

	//Start in zero
	pwmWrite(_pin_pwm, 0);
	digitalWrite(_pin_in1, 0);
	digitalWrite(_pin_in2, 0);
}

void TB6612FNG::pwm(char pwm) {
	char power = pwm > 0 ? pwm : -pwm;
	Serial.println(power);
	pwmWrite(_pin_pwm, map(power, 0, 100, 0, 761.0));

	digitalWrite(_pin_in1, pwm >=  0 ? 1 : 0);
  digitalWrite(_pin_in2, pwm >   0 ? 0 : 1);
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
