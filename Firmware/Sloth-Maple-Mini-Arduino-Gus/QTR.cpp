// #include "QTR.h"
//
//
// QTR::QTR(unsigned char *pins, unsigned char numSensors, unsigned char emitterPin)
// {
// 	_pins = pins;
// 	_numSensors = numSensors;
// 	_emitterPin = emitterPin;
// 	sensorValues[_numSensors];
// 	QTRSensorsAnalog qtra(_pins, _numSensors, NUM_SAMPLES_PER_SENSOR, _emitterPin);
//
// }
// int QTR::read(){
// 	qtra.read(sensorValues, QTR_EMITTERS_ON);
//   return sensorValues;
// }
//
// void QTR::calibrate(){
// 	LOG.print("Calibrating sensors...");
// 	digitalWrite(PIN_LED, 1);
// 	for (int i = 0; i < 1000; i++)
// 		qtra.calibrate(true);
// 	LOG.println("Done.");
// 	delay(2000);
// 	digitalWrite(PIN_LED, 0);
// }
// void QTR::resetCalibration(){
// 	qtra.resetCalibration();
// }
