#include "_config.h"
#include "_types.h"
#include "lineReader.h"
#include "mbed.h"

float values[6];
int SENSOR_MIN = 10;
int SENSOR_MAX = 100;

void LineReader::init(){
/*
	inLR_S1(PIN_LR_S1);
	inLR_S2(PIN_LR_S2);
	inLR_S3(PIN_LR_S3);
	inLR_S4(PIN_LR_S4);
	inLR_S5(PIN_LR_S5);
*/
}

void LineReader::readValues(){
	values[0] = inLR_S0.read();		
	values[1] = inLR_S1.read();		
	values[2] = inLR_S2.read();		
	values[3] = inLR_S3.read();		
	values[4] = inLR_S4.read();		
	values[5] = inLR_S5.read();		
}

int LineReader::getValue(int index){
	return values[index];
}

float LineReader::getPosition(){
  float weighted_sum = 0;
  float sum = 0;
  for(int i = 0; i < 6; i++){
    float value = -(float)getValue(i) / (SENSOR_MAX - SENSOR_MIN) + 1.0;
    value = min(max(0.0, value), 1.0);
    //  Serial.print(i);
    //  Serial.print(" : ");
    //  Serial.print(value);
    //  Serial.print("\t");
    weighted_sum = weighted_sum + value  * (i - 7);
    sum = sum + value;
  }
  // Serial.println();
  float position = -((weighted_sum / sum) - 4.5) / 3.5;
  return position;
}
