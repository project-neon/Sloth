#ifndef LINE_READER_H
#define LINE_READER_H

#include "mbed.h"
#include "_config.h"
#include "_types.h"

//Instanciando 
AnalogIn inLR_S0(PIN_LR_S0);
AnalogIn inLR_S1(PIN_LR_S1);
AnalogIn inLR_S2(PIN_LR_S2);
AnalogIn inLR_S3(PIN_LR_S3);
AnalogIn inLR_S4(PIN_LR_S4);
AnalogIn inLR_S5(PIN_LR_S5);
DigitalIn inMarkingL(PIN_LR_S0);
DigitalIn inMarkingR(PIN_LR_S0);

class LineReader{
public:
	//LineReader(PinName pin);
	static void init();
  static void readValues();
  static int getValue(int index);
  static float getPosition();

private:
/*AnalogIn 			inLR_S0;
	AnalogIn 			inLR_S1;
	AnalogIn 			inLR_S2;
	AnalogIn 			inLR_S3;
	AnalogIn 			inLR_S4;
	AnalogIn 			inLR_S5;
	DigitalIn 		inMarkingL;
	DigitalIn 		inMarkingR;
*/
};

#endif
