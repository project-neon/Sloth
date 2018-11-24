#include "_config.h"
#include "STRUCTURES.h"

#ifndef SETTINGSSPEED_H
#define SETTINGSSPEED_H

float speedbase = 20;
// float kpdir = 0.022;
// float kidir = 0.0;
// float kddir = 0.0015;

float kpdir = 2.0;
float kidir = 0.0;
float kddir = 0.0;

#define CONSTANTE 1000

Setup Normal     = {speedbase, kpdir/CONSTANTE, kidir/CONSTANTE, kddir/CONSTANTE};

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

Setup k2[] { // SlowCurve,Curve, FastCurve, Straight, Stop
  // 150mm x 75mm
  {0.30, 0.00020, 0.000000, 0.0000035},
  {0.50, 0.00040, 0.000000, 0.0000060},
  {1.00, 0.00030, 0.000000, 0.0000100},
  {1.00, 0.00020, 0.000000, 0.0000075},
  {0.10, 0.00010, 0.000000, 0.0000010}
};

Setup k3[] { // SlowCurve,Curve, FastCurve, Straight, Stop
  // MOTORS 30:1  120mm x 75mm
  {0.30, 0.00030, 0.000000, 0.0000030},
  // {0.70, 0.00020, 0.000000, 0.0000060},
  // {0.85, 0.00022, 0.000000, 0.000015},
  {0.50, 0.00040, 0.000000, 0.0000060},
  {0.85, 0.00022, 0.000000, 0.000025},
  // {1.00, 0.00022, 0.000000, 0.000025},
  // {0.85, 0.00014, 0.000000, 0.0000150},
  {1.00, 0.00022, 0.000000, 0.000025},
  {0.10, 0.00010, 0.000000, 0.0000010}
};




#endif
