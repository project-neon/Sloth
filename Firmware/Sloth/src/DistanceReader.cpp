#include "DistanceReader.h"

// Encoders
static QEI LeftEncoder (PIN_ENC1_A, PIN_ENC1_B, NC, PULSES_PER_REV);
static QEI RightEncoder (PIN_ENC2_A, PIN_ENC2_B, NC, PULSES_PER_REV);

void DistanceReader::reset(){
  DistanceReader::resetLeft();
  DistanceReader::resetRight();
}

void DistanceReader::resetRight(){
  RightEncoder.reset();
}

void DistanceReader::resetLeft(){
  LeftEncoder.reset();
}

int DistanceReader::getPulsesRight(){
  return RightEncoder.getPulses();
}

int DistanceReader::getPulsesLeft(){
  return LeftEncoder.getPulses();
}

float DistanceReader::getDistanceLeft(){
  return DistanceReader::pulsesToDistance(getPulsesLeft());
}

float DistanceReader::getDistanceRight(){
  return DistanceReader::pulsesToDistance(getPulsesRight());
}

float DistanceReader::getDistance(){
  return (DistanceReader::getDistanceRight() + DistanceReader::getDistanceLeft()) / 2.0;
}

float DistanceReader::getDifference(){
  return (DistanceReader::getDistanceRight() - DistanceReader::getDistanceLeft());
}

float DistanceReader::pulsesToDistance(int pulses) {
  // revolutions * wheel perimeter
  float revolutions = (float) pulses / (float) PULSES_PER_REV;
  float wheel_perimeter = (2.0 * WHEEL_RADIUS * M_PI);
  return revolutions * wheel_perimeter;
}
