#include "_config.h"
#include "settingsSpeed.h"

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
