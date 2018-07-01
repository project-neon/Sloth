#include "QTRSensors.h"
#include "_config.h"

#ifndef LINE_READER_H
#define LINE_READER_H

class LineReader {
public:
  static void calibrate();
  static float getPosition();
  static int getValue(int index);

private:
  // Line Reader
  PinName pins[NUM_SENSORS] = {
      PIN_LR_S0, // Most Left Sensor
      PIN_LR_S1,
      PIN_LR_S2,
      PIN_LR_S3,
      PIN_LR_S4,
      PIN_LR_S5 // Most Right Sensor
  };

  QTRSensorsAnalog QTRSensor(pins,
      NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);

  unsigned int values[NUM_SENSORS];
};

#endif
