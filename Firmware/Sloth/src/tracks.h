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

Mark HACKPULICA_V2[] = { // Distance in meters, Aceleration, Constants of gain (PID)
  //Tests for Straights
  {00.15 - 00.00, +1.0, GAIN_NUMBER[Straight]},
  {00.61 - 00.00, -5.0, GAIN_NUMBER[SlowCurve]},
  {02.27 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {02.47 - 00.00, -5.0, GAIN_NUMBER[SlowCurve]},
  {02.84 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {03.80 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {04.17 - 00.35, +1.0, GAIN_NUMBER[Straight]},
  {04.45 - 00.00, -5.0, GAIN_NUMBER[SlowCurve]},
  {06.00 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {06.28 - 00.00, -5.0, GAIN_NUMBER[SlowCurve]},
  {06.67 - 00.00, +1.0, GAIN_NUMBER[Straight]},
  {07.60 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {07.97 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {FINAL_TARGET_POSITION, +0.5, GAIN_NUMBER[Straight]}
};

Mark HACKPULICA_NORMAL[] = { // Distance in meters, Aceleration, Constants of gain (PID)
  //Tests for Straights
  {00.41 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {00.71 - 00.00, -5.0, GAIN_NUMBER[SlowCurve]},
  {01.90 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {03.44 - 00.00, -2.0, GAIN_NUMBER[FastCurve]},
  {03.86 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {04.23 - 00.00, -5.0, GAIN_NUMBER[SlowCurve]},
  {04.60 - 00.35, +1.0, GAIN_NUMBER[Straight]},
  {05.51 - 00.00, -1.0, GAIN_NUMBER[Curve]},
  {06.10 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {FINAL_TARGET_POSITION, +1.5, GAIN_NUMBER[Straight]}
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

Mark WC14_2018[] = {
{01.25 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //01
{01.67 - 00.00, -10, GAIN_NUMBER[Curve]},      //02
{02.44 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //03
{03.15 - 00.00, -10, GAIN_NUMBER[Curve]},      //04
{03.36 - 00.00, -1.0, GAIN_NUMBER[Curve]},      //05
{03.95 - 00.20, +1.5, GAIN_NUMBER[Straight]},   //06
// {04.14 - 00.00, -10, GAIN_NUMBER[Curve]},      //07
// {04.31 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //08
{04.66 - 00.00, -10, GAIN_NUMBER[Curve]},      //09
{05.20 - 00.20, +1.5, GAIN_NUMBER[Straight]},   //10
{05.45 - 00.00, -10, GAIN_NUMBER[Curve]},      //11
{05.97 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //12
{06.23 - 00.00, -10, GAIN_NUMBER[Curve]},      //13
{07.39 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //14
{07.61 - 00.00, -10, GAIN_NUMBER[Curve]},      //15
{07.91 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //16
{08.27 - 00.00, -10, GAIN_NUMBER[Curve]},      //17
{09.61 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //18
{10.14 - 00.00, -10, GAIN_NUMBER[Curve]},      //19
{11.62 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //20
{12.09 - 00.00, -10, GAIN_NUMBER[Curve]},      //21
{13.26 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //22
{13.51 - 00.00, -10, GAIN_NUMBER[Curve]},      //23
{14.36 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //24
{14.55 - 00.00, -10, GAIN_NUMBER[Curve]},      //25
{16.12 - 00.00, +1.5, GAIN_NUMBER[FastCurve]},  //26
{16.67 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //27
{16.91 - 00.00, -10, GAIN_NUMBER[SlowCurve]},   //28
{17.74 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //29
{18.04 - 00.00, -10, GAIN_NUMBER[Curve]},      //30
{19.12 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //31
{19.46 - 00.00, -10, GAIN_NUMBER[Curve]},      //32
{22.30 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //33
{22.68 - 00.00, -10, GAIN_NUMBER[Curve]},      //34

{23.20 - 00.00, +1.0, GAIN_NUMBER[Straight]},           //35


  {FINAL_TARGET_POSITION, +1.5, GAIN_NUMBER[Straight]}
  // {FINAL_TARGET_POSITION, -1.0, Stop} // 21 End Track
};

Mark WC14_2018_SAFE[] = {
{01.25 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //01
{01.67 - 00.00, -10, GAIN_NUMBER[Curve]},      //02
{02.44 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //03
{03.15 - 00.00, -10, GAIN_NUMBER[Curve]},      //04
{03.36 - 00.00, -1.0, GAIN_NUMBER[Curve]},      //05
{03.95 - 00.20, +1.5, GAIN_NUMBER[Straight]},   //06
// {04.14 - 00.00, -10, GAIN_NUMBER[Curve]},      //07
// {04.31 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //08
{04.66 - 00.00, -10, GAIN_NUMBER[Curve]},      //09
{05.20 - 00.20, +1.5, GAIN_NUMBER[Straight]},   //10
{05.45 - 00.00, -10, GAIN_NUMBER[Curve]},      //11
{05.97 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //12
{06.23 - 00.00, -10, GAIN_NUMBER[Curve]},      //13
{07.39 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //14
// {07.61 - 00.00, -10, GAIN_NUMBER[Curve]},      //15
// {07.91 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //16
{08.27 - 00.00, -10, GAIN_NUMBER[Curve]},      //17
{09.61 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //18
{10.14 - 00.00, -10, GAIN_NUMBER[Curve]},      //19
{11.62 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //20
{12.09 - 00.00, -10, GAIN_NUMBER[Curve]},      //21
{13.26 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //22
{13.51 - 00.00, -10, GAIN_NUMBER[Curve]},      //23
{14.36 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //24
{14.55 - 00.00, -10, GAIN_NUMBER[Curve]},      //25
{16.12 - 00.00, +1.5, GAIN_NUMBER[FastCurve]},  //26
{16.67 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //27
{16.91 - 00.00, -10, GAIN_NUMBER[SlowCurve]},   //28
{17.74 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //29
{18.04 - 00.00, -10, GAIN_NUMBER[Curve]},      //30
{19.12 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //31
{19.46 - 00.00, -10, GAIN_NUMBER[Curve]},      //32
{22.30 - 00.15, +1.5, GAIN_NUMBER[Straight]},   //33
{22.68 - 00.00, -10, GAIN_NUMBER[Curve]},      //34

{23.20 - 00.00, +1.0, GAIN_NUMBER[Straight]},           //35


  {FINAL_TARGET_POSITION, +1.5, GAIN_NUMBER[Straight]}
  // {FINAL_TARGET_POSITION, -1.0, Stop} // 21 End Track
};

#endif
