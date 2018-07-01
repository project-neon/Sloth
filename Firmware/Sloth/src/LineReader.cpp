#include "QTRSensors.h"
#include "_config.h"

#include "LineReader.h"

// Function to calibrate the sensors
void LineReader::calibrate(int nsamples) {
  for (int i = 0; i < nsamples; i++)
    QTRSensor.calibrate(true);
}

// Return the value of a sensor by index
float LineReader::getValue(int index) {
  return values[index];
}

float LineReader::getPosition() {
  // Position of the line: (left)-2500 to 2500(right)
  return (float) (QTRSensor.readLine(sensorvalues, QTR_EMITTERS_ON, WHITE_LINE) - 2500.0) / 2500.0;
}
