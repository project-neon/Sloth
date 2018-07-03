#include "QTRSensors.h"
#include "_config.h"

#ifndef LINE_READER_H
#define LINE_READER_H

class LineReader {
public:
  static void calibrate(int nsamples = 100);
  static float getPosition();
  static int getValue(int index);
};

#endif
