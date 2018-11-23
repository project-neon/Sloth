#include "Encoder.h"

int _pulses=0;
uint8_t _pinA;
uint8_t _pinB;

void encoderChannelA(){
	if (digitalRead(_pinA)== HIGH) {
    	_pulses++;
	}
	else{
		_pulses--;
	}
}
void encoderChannelB(){
	if (digitalRead(_pinB)== HIGH) {
    	_pulses--;
	}
	else{
		_pulses++;
	}
}

Encoder::Encoder(uint8_t pinA, uint8_t pinB, int pulsesPerRev, float wheelRadius)
{
	_pulsesPerRev = pulsesPerRev > 0 ? pulsesPerRev : 0;
	_wheelRadius = wheelRadius > 0 ? wheelRadius : 0;
	_pinA = pinA;
	_pinB = pinB;
	_pulses=0;
	_revolutions=0;
	_distance=0;


	attachInterrupt(digitalPinToInterrupt(_pinA), encoderChannelA, RISING);
  	attachInterrupt(digitalPinToInterrupt(_pinB), encoderChannelB, RISING);
}



int Encoder::getPulses(){
	return _pulses;
}
float Encoder::getRevolutions(){
	_revolutions = _pulsesPerRev > 0 ?  _pulses/_pulsesPerRev : 0;
	return _revolutions;
}
float Encoder::getDistance(){
	return 2*PI*_wheelRadius*_revolutions;
}

void Encoder::reset(){
	_revolutions=0;
	_pulses=0;
}



