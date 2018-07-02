#include "QTRSensors.h"
#include "_config.h"

#include "LineReader.h"

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
// Function to calibrate the sensors
void LineReader::calibrate(int nsamples) {
  for (int i = 0; i < nsamples; i++)
    QTRSensor.calibrate(true);
}

// Return the value of a sensor by index
int LineReader::getValue(int index) {
  return values[index];
}

float LineReader::getPosition() {
  // Position of the line: (left)-2500 to 2500(right)
  return (float) ((QTRSensor.readLine(values, QTR_EMITTERS_ON, WHITE_LINE) - 2500.0)/2500);
}
