#include "_config.h"
#include "main.h"

#ifndef SETTINGSSPEED_H
#define SETTINGSSPEED_H

Setup k0[] {
  // Target Speed, kp, ki, kd
  {0.62, 0.00025, 0.000000, 0.0000050}, // Slow Curve
  {0.60, 0.00022, 0.000000, 0.0000050}, // Curve
  {0.70, 0.00022, 0.000000, 0.0000075}, // FastCurve
  {1.00, 0.00018, 0.000000, 0.0000075}, // Straight
  {0.10, 0.00010, 0.000000, 0.0000010}  // Stop
};

Setup k1[] { // SlowCurve,Curve, FastCurve, Straight, Stop
  {0.30, 0.00020, 0.000000, 0.0000035},
  {0.40, 0.00020, 0.000000, 0.0000035},
  {0.70, 0.00022, 0.000000, 0.0000075},
  {1.00, 0.00018, 0.000000, 0.0000075},
  {0.10, 0.00010, 0.000000, 0.0000010}
};

#endif
