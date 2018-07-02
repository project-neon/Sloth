#include "_config.h"
#include "DistanceReader.h"

// Encoders
QEI LeftEncoder (PIN_ENC1_A, PIN_ENC1_B, NC, PULSES_PER_REV); // Left Encoder
QEI RightEncoder (PIN_ENC2_A, PIN_ENC2_B, NC, PULSES_PER_REV); // Right Encoder

float currentPosition; // Robot current position in the track
float leftDistance; // left distance by encoder (m)
float rightDistance; // right distance by encoder (m)

// leftDistance = PULSES2DISTANCE(LeftEncoder.getPulses());
// rightDistance = PULSES2DISTANCE(RightEncoder.getPulses());
// currentPosition = AVG(leftDistance, rightDistance) + POSITION_FIX; //get average


void DistanceReader::resetRight(){
  RightEncoder.reset();
}
void DistanceReader::resetLeft(){
  LeftEncoder.reset();
}
void DistanceReader::reset(){
   DistanceReader::resetLeft();
   DistanceReader::resetRight();
}
int DistanceReader::getPulsesRight(){
  return RightEncoder.getPulses();
}
int DistanceReader::getPulsesLeft(){
  return LeftEncoder.getPulses();
}
float DistanceReader::pulsesToDistance(int pulses){
  return PULSES2DISTANCE(pulses);
}
int DistanceReader::getDistanceLeft(){
  return DistanceReader::pulsesToDistance(getPulsesLeft());
}
int DistanceReader::getDistanceRight(){
  return DistanceReader::pulsesToDistance(getPulsesRight());
}
int DistanceReader::getDistance(){
  return (DistanceReader::getDistanceRight() + DistanceReader::getDistanceLeft()) / 2;
}
int DistanceReader::getDifference(){
  return (DistanceReader::getDistanceRight() - DistanceReader::getDistanceLeft());
}
