// Hardware libraries
#include "mbed.h"
#include "QEI.h"

// User libraries
#include "_config.h"

#ifndef DISTANCE_READER_H
#define DISTANCE_READER_H

class DistanceReader {
public:
  static void reset();
  static void resetRight();
  static void resetLeft();
  static int getPulsesRight();
  static int getPulsesLeft();
  static float getDistanceLeft();
  static float getDistanceRight();
  static float getDistance();
  static float getDifference();
  static float pulsesToDistance(int pulses);
};

#endif
