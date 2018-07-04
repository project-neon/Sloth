#include "_config.h"
#include "settingsSpeed.h"

#ifndef TRACKS_H
#define TRACKS_H
/*
  This file contains the tracks that the robot has already done.
*/

Mark SMILE_2018[] = { // Distance in meters, Aceleration, Constants of gain (PID)
  {00.78, +1.5, GAIN_NUMBER[Straight]},
  {01.2, -2, GAIN_NUMBER[Curve]},
  {02.60, +1.0, GAIN_NUMBER[Straight]},
  {03.2, -1.0, GAIN_NUMBER[Curve]},
  {04.6, +1.0, GAIN_NUMBER[Straight]},
  {05.25, -1.0, GAIN_NUMBER[Curve]},
  {06.0, +1.0, GAIN_NUMBER[Straight]},
  {07.25, -1.0, GAIN_NUMBER[FastCurve]},
  {08.5, +1.0, GAIN_NUMBER[Straight]},
  {08.95, -1.0, GAIN_NUMBER[FastCurve]},
  {09.6, +1.0, GAIN_NUMBER[Straight]},
  {10.80, -1.0, GAIN_NUMBER[FastCurve]},
  {11.0, +1.0, GAIN_NUMBER[Straight]},
  {11.50, -1.0, GAIN_NUMBER[Curve]},
  {11.9, +1.0, GAIN_NUMBER[Straight]},
  {12.60, -1, GAIN_NUMBER[Curve]},
  {13.2, +1.00, GAIN_NUMBER[FastCurve]},

  {FINAL_TARGET_POSITION, +1.5, GAIN_NUMBER[Straight]}
  // {FINAL_TARGET_POSITION, -1.0, Stop} // 21 End Track
};

Mark TEST[] = { // Distance in meters, Aceleration, Constants of gain (PID)
  {00.1, +1.5, GAIN_NUMBER[Straight]},
  {01.0, -2, GAIN_NUMBER[Curve]},
  {01.5, -2, GAIN_NUMBER[SlowCurve]},
  {FINAL_TARGET_POSITION, +1.5, GAIN_NUMBER[Straight]}
  // {FINAL_TARGET_POSITION, -1.0, Stop} // 21 End Track
};

Mark HACKPULICA_OLD[] = { // Distance in meters, Aceleration, Constants of gain (PID)
  {00.78, +1.0, GAIN_NUMBER[Straight]},
  {01.35, -10.0, GAIN_NUMBER[SlowCurve]},
  {01.60, +1.0, GAIN_NUMBER[Straight]},
  {02.10, -10.0, GAIN_NUMBER[Curve]},
  {02.35, +1.0, GAIN_NUMBER[Straight]},//ALTERAR
  {03.00, -10.0, GAIN_NUMBER[Curve]},
  {03.35, +1.0, GAIN_NUMBER[Straight]},
  {04.00, -10.0, GAIN_NUMBER[Curve]},
  {04.35, +1.0, GAIN_NUMBER[Straight]},
  {05.35, -10.0, GAIN_NUMBER[Curve]},
  {06.50, +1.0, GAIN_NUMBER[Straight]},
  {08.10, -10.0, GAIN_NUMBER[Curve]},
  {08.90, +1.0, GAIN_NUMBER[FastCurve]},
  {09.05, +1.0, GAIN_NUMBER[Straight]},
  {11.20, -10.0, GAIN_NUMBER[SlowCurve]},
  {11.35, +1.0, GAIN_NUMBER[Straight]},
  {12.55, -10.0, GAIN_NUMBER[Curve]},

  {FINAL_TARGET_POSITION, +0.5, GAIN_NUMBER[Straight]}
  // {FINAL_TARGET_POSITION, -1.0, Stop} // 21 End Track
};

Mark HACKPULICA[] = { // Distance in meters, Aceleration, Constants of gain (PID)
  {00.15, +1.0, GAIN_NUMBER[Straight]},
  {00.75, -10.0, GAIN_NUMBER[SlowCurve]},
  {01.10, +0.5, GAIN_NUMBER[Straight]},
  {01.45, -10.0, GAIN_NUMBER[Curve]},
  {01.85, +0.5, GAIN_NUMBER[Straight]},
  {02.40, -10.0, GAIN_NUMBER[Curve]},
  {02.85, +1.0, GAIN_NUMBER[Straight]},
  {03.40, -10.0, GAIN_NUMBER[Curve]},
  {03.80, +0.5, GAIN_NUMBER[Straight]},
  {04.75, -10.0, GAIN_NUMBER[Curve]},
  {05.95, +0.5, GAIN_NUMBER[Straight]},
  {07.25, -10.0, GAIN_NUMBER[Curve]},
  {08.15, +1.0, GAIN_NUMBER[FastCurve]},
  {08.40, +1.0, GAIN_NUMBER[Straight]},
  {10.20, -10.0, GAIN_NUMBER[SlowCurve]},
  {10.70, +1.0, GAIN_NUMBER[Straight]},
  {11.6, -10.0, GAIN_NUMBER[Curve]},

  {FINAL_TARGET_POSITION, +0.5, GAIN_NUMBER[Straight]}
};

Mark IRON_2018[] = {
  {00.78, +1.5, GAIN_NUMBER[Straight]},
  {01.2, -2, GAIN_NUMBER[Curve]},
  {02.60, +1.0, GAIN_NUMBER[Straight]},
  {03.2, -1.0, GAIN_NUMBER[Curve]},
  {04.6, +1.0, GAIN_NUMBER[Straight]},
  {05.25, -1.0, GAIN_NUMBER[Curve]},
  {06.0, +1.0, GAIN_NUMBER[Straight]},
  {07.25, -1.0, GAIN_NUMBER[FastCurve]},
  {08.5, +1.0, GAIN_NUMBER[Straight]},
  {08.95, -1.0, GAIN_NUMBER[FastCurve]},
  {09.6, +1.0, GAIN_NUMBER[Straight]},
  {10.80, -1.0, GAIN_NUMBER[FastCurve]},
  {11.0, +1.0, GAIN_NUMBER[Straight]},
  {11.50, -1.0, GAIN_NUMBER[Curve]},
  {11.9, +1.0, GAIN_NUMBER[Straight]},
  {12.60, -1, GAIN_NUMBER[Curve]},
  {13.2, +1.00, GAIN_NUMBER[FastCurve]},

  {FINAL_TARGET_POSITION, +1.5, GAIN_NUMBER[Straight]}
  // {FINAL_TARGET_POSITION, -1.0, Stop} // 21 End Track
};

#endif
