#include "QEI.h"
#include "_config.h"

#ifndef DISTANCE_READER_H
#define DISTANCE_READER_H

class DistanceReader {
public:
  static void init();
  static void resetRight();
  static void resetLeft();
  static void reset();
  static int getPulsesRight();
  static int getPulsesLeft();
  static int getDistanceLeft();
  static int getDistanceRight();
  static int getDistance();
  static int getDifference();
  static float pulsesToDistance(int pulses);
};

#endif
