#include "_config.h"
#include "settingsSpeed.h"

#ifndef TRACKS_H
#define TRACKS_H
/*
  This file contains the tracks that the robot has already done.
*/
Mark TECH_CHALLENGE[] = { // Distance in meters, Aceleration, Constants of gain (PID)
  {00.30-OFFSET_ACELERATION, ACCELERATION_UP, GAIN_NUMBER[Curve]},   // 1 - 00.30
  {00.55+OFFSET_DESACELERATION, ACCELERATION_DOWN, GAIN_NUMBER[Curve]},      // 2 - 00.70
  {01.95-OFFSET_ACELERATION, ACCELERATION_UP, GAIN_NUMBER[Straight]},   // 3 - 02.05
  {02.75+OFFSET_DESACELERATION, ACCELERATION_DOWN, GAIN_NUMBER[Curve]},      // 4 - 02.70
  {04.10-OFFSET_ACELERATION, ACCELERATION_UP, GAIN_NUMBER[Straight]},   // 5 - 04.00
  {04.45+OFFSET_DESACELERATION, ACCELERATION_DOWN, GAIN_NUMBER[Curve]},      // 6 - 04.60
  {05.40-OFFSET_ACELERATION, ACCELERATION_UP, GAIN_NUMBER[Straight]},   // 7 - 05.55
  {06.75+OFFSET_DESACELERATION, ACCELERATION_DOWN, GAIN_NUMBER[FastCurve]},  // 8 - 06.55
  {07.90-OFFSET_ACELERATION, ACCELERATION_UP, GAIN_NUMBER[Straight]},   // 9 - 07.80
  {08.45+OFFSET_DESACELERATION, ACCELERATION_DOWN, GAIN_NUMBER[Curve]},//10 - 08.20
  {09.25-OFFSET_ACELERATION, ACCELERATION_UP, GAIN_NUMBER[Straight]},//11 - 09.00
  // {10.35+OFFSET_DESACELERATION, ACCELERATION_DOWN, GAIN_NUMBER[FastCurve]},// 12 - 10.00
  // {10.65-OFFSET_ACELERATION, ACCELERATION_UP, GAIN_NUMBER[Straight]},//13 - 10.30
  {10.65+OFFSET_DESACELERATION, ACCELERATION_DOWN, GAIN_NUMBER[FastCurve]},// 12 - 10.00
  {11.15+OFFSET_DESACELERATION, ACCELERATION_DOWN, GAIN_NUMBER[Curve]},//14 - 10.70
  {11.60-OFFSET_ACELERATION, ACCELERATION_UP, GAIN_NUMBER[Straight]},//15 - 11.15
  // {11.70+OFFSET_DESACELERATION, ACCELERATION_DOWN, GAIN_NUMBER[Curve]},//16 - 11.70
  {12.75-OFFSET_ACELERATION, ACCELERATION_UP, GAIN_NUMBER[Curve]},//17 - 12.70

  {FINAL_TARGET_POSITION, +5.0, GAIN_NUMBER[Straight]}

  // {FINAL_TARGET_POSITION, -1.0, Stop} // 21 End Track
};

Mark HACKPULICA_RETAS[] = { // Distance in meters, Aceleration, Constants of gain (PID)
  {2.3, +5.0, GAIN_NUMBER[Straight]},
  {3.4, -2, GAIN_NUMBER[SlowCurve]},
  {6.1, +5.0, GAIN_NUMBER[Straight]},
  {7.0, -5.0, GAIN_NUMBER[SlowCurve]},
  {9.86, +5.0, GAIN_NUMBER[Straight]},
  {10.9, -5.0, GAIN_NUMBER[SlowCurve]},
  {12.8, +5.0, GAIN_NUMBER[Straight]},
  {FINAL_TARGET_POSITION, +1.5, GAIN_NUMBER[Straight]}
  // {FINAL_TARGET_POSITION, -1.0, Stop} // 21 End Track
};

Mark HACKPULICA_NORMAL_NEW[] = { // Distance in meters, Aceleration, Constants of gain (PID)
  {3.2, +5.0, GAIN_NUMBER[Curve]},
  {5.1, +5.0, GAIN_NUMBER[Curve]},
  {6.8, -2, GAIN_NUMBER[SlowCurve]},
  {8.7, +5.0, GAIN_NUMBER[Curve]},
  {10.6, -5.0, GAIN_NUMBER[Curve]},
  {10.8, +5.0, GAIN_NUMBER[Curve]},
  {12.0, -5.0, GAIN_NUMBER[SlowCurve]},
  {12.2, +5.0, GAIN_NUMBER[Curve]},
  {FINAL_TARGET_POSITION, +5.0, GAIN_NUMBER[Curve]}
  // {FINAL_TARGET_POSITION, -1.0, Stop} // 21 End Track
};

Mark SMILE_2018[] = { // Distance in meters, Aceleration, Constants of gain (PID)
  {00.78, +1.5, GAIN_NUMBER[Straight]},       //01
  {01.2, -2, GAIN_NUMBER[Curve]},       //02
  {02.60, +1.0, GAIN_NUMBER[Straight]},       //03
  {03.2, -1.0, GAIN_NUMBER[Curve]},       //04
  {04.6, +1.0, GAIN_NUMBER[Straight]},        //05
  {05.25, -1.0, GAIN_NUMBER[Curve]},        //06
  {06.0, +1.0, GAIN_NUMBER[Straight]},        //07
  {07.25, -1.0, GAIN_NUMBER[FastCurve]},        //08
  {08.5, +1.0, GAIN_NUMBER[Straight]},        //09
  {08.95, -1.0, GAIN_NUMBER[FastCurve]},        //10
  {09.6, +1.0, GAIN_NUMBER[Straight]},        //11
  {10.80, -1.0, GAIN_NUMBER[FastCurve]},        // 12
  {11.0, +1.0, GAIN_NUMBER[Straight]},        //13
  {11.50, -1.0, GAIN_NUMBER[Curve]},        //14
  {11.9, +1.0, GAIN_NUMBER[Straight]},        //15
  {12.60, -1, GAIN_NUMBER[Curve]},        //16
  {13.2, +1.00, GAIN_NUMBER[FastCurve]},        //17

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

Mark HACKPULICA_NORMAL_10_1[] = { // Distance in meters, Aceleration, Constants of gain (PID)

  {00.01 - 00.00, +1.0, GAIN_NUMBER[Curve]},
  {01.13 - 00.00, -10.0, GAIN_NUMBER[Curve]},
  // {02.25 - 00.00, +1.0, GAIN_NUMBER[Straight]},
  // {00.41 - 00.35, +1.0, GAIN_NUMBER[Straight]},
  // {00.77 - 00.00, -10.0, GAIN_NUMBER[SlowCurve]},
  // {01.98 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  // {03.55 - 00.00, -2.0, GAIN_NUMBER[Curve]},
  // {03.99 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  // {04.43 - 00.00, -10.0, GAIN_NUMBER[SlowCurve]},
  // {04.82 - 00.35, +1.0, GAIN_NUMBER[Straight]},
  // {05.75 - 00.00, -1.0, GAIN_NUMBER[Curve]},
  // {06.06 - 00.30, +1.0, GAIN_NUMBER[Straight]},
  {FINAL_TARGET_POSITION-0.2, +1.5, GAIN_NUMBER[Straight]},
  {FINAL_TARGET_POSITION, -10.0, GAIN_NUMBER[Stop]},
};

Mark HACKPULICA_NORMAL_10_1_LM[] = { // Distance in meters, Aceleration, Constants of gain (PID)

  {00.41 - 00.35, +0.5, GAIN_NUMBER[Straight]},
  {00.88 - 00.00, -10.0, GAIN_NUMBER[Curve]},
  {02.08 - 00.35, +0.5, GAIN_NUMBER[Straight]},
  {03.80 - 00.00, -10.0, GAIN_NUMBER[Curve]},
  {04.23 - 00.30, +0.5, GAIN_NUMBER[Straight]},
  {04.77 - 00.00, -2.0, GAIN_NUMBER[SlowCurve]},
  {05.15 - 00.30, +0.5, GAIN_NUMBER[Straight]},
  {05.88 - 00.00, -10.0, GAIN_NUMBER[Curve]},
  {06.47 - 00.30, +0.5, GAIN_NUMBER[Straight]},
  {FINAL_TARGET_POSITION-0.2, +1.5, GAIN_NUMBER[Straight]},
  {FINAL_TARGET_POSITION, -10.0, GAIN_NUMBER[Stop]},
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
{05.20 - 00.30, +1.5, GAIN_NUMBER[Straight]},   //10
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
  {01.25 - 00.30, +1.0, GAIN_NUMBER[Straight]},     //01
  {01.67 - 00.00, -10, GAIN_NUMBER[Curve]},         //02
  {02.44 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //03
  {03.15 - 00.00, -10, GAIN_NUMBER[Curve]},         //04
  {03.36 - 00.00, -1.0, GAIN_NUMBER[Curve]},        //05
  {03.95 - 00.20, +1.0, GAIN_NUMBER[Straight]},     //06
  // {04.14 - 00.00, -10, GAIN_NUMBER[Curve]},      //07
  // {04.31 - 00.15, +1.0, GAIN_NUMBER[Straight]},  //08
  {04.66 - 00.00, -10, GAIN_NUMBER[Curve]},         //09
  {05.20 - 00.20, +1.0, GAIN_NUMBER[Straight]},     //10
  {05.45 - 00.00, -10, GAIN_NUMBER[Curve]},         //11
  {05.97 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //12
  {06.23 - 00.00, -10, GAIN_NUMBER[Curve]},         //13
  {07.39 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //14
  // {07.61 - 00.00, -10, GAIN_NUMBER[Curve]},      //15
  // {07.91 - 00.15, +1.0, GAIN_NUMBER[Straight]},  //16
  {08.27 - 00.00, -10, GAIN_NUMBER[Curve]},         //17
  {09.61 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //18
  {10.14 - 00.00, -10, GAIN_NUMBER[Curve]},         //19
  {11.62 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //20
  {12.09 - 00.00, -10, GAIN_NUMBER[Curve]},         //21
  {13.26 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //22
  {13.51 - 00.00, -10, GAIN_NUMBER[Curve]},         //23
  {14.36 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //24
  {14.55 - 00.00, -10, GAIN_NUMBER[Curve]},         //25
  {16.12 - 00.00, +1.0, GAIN_NUMBER[FastCurve]},    //26
  {16.67 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //27
  {16.91 - 00.00, -10, GAIN_NUMBER[SlowCurve]},     //28
  {17.74 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //29
  {18.04 - 00.00, -10, GAIN_NUMBER[Curve]},         //30
  {19.12 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //31
  {19.46 - 00.00, -10, GAIN_NUMBER[Curve]},         //32
  {22.30 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //33
  {22.68 - 00.00, -10, GAIN_NUMBER[Curve]},         //34
  {23.20 - 00.00, +1.0, GAIN_NUMBER[Straight]},     //35
  {FINAL_TARGET_POSITION, +1.0, GAIN_NUMBER[Straight]}
  // {FINAL_TARGET_POSITION, -1.0, Stop} // 21 End Track
};

Mark WC14_2018_LEFT_MOTORS[] = {
  {01.24 - 00.20, +1.0, GAIN_NUMBER[Straight]},     //01
  // {01.56 - 00.00, -10, GAIN_NUMBER[Curve]},         //02
  // {02.30 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //03
  // {02.77 - 00.00, -10, GAIN_NUMBER[Curve]},         //04
  // {03.03 - 00.00, -1.0, GAIN_NUMBER[Curve]},        //05
  // {03.63 - 00.15, -1.0, GAIN_NUMBER[Straight]},        //05
  // {03.88 - 00.20, +1.0, GAIN_NUMBER[Curve]},     //06
  // {04.07 - 00.15, -10, GAIN_NUMBER[Straight]},      //07
  // {04.58 - 00.15, +1.0, GAIN_NUMBER[Curve]},  //08
  {05.03 - 00.10, -10.0, GAIN_NUMBER[Curve]},         //09
  {05.26 - 00.00, -10.0, GAIN_NUMBER[SlowCurve]},     //10
  {05.76 - 00.10, +0.5, GAIN_NUMBER[Curve]},         //11
  {05.92 - 00.00, -10.0, GAIN_NUMBER[SlowCurve]},     //12
  {07.06 - 00.15, +1.0, GAIN_NUMBER[Straight]},         //13
  // {07.17 - 00.00, +1.0, GAIN_NUMBER[Curve]},     //14
  // {07.42 - 00.15, -10, GAIN_NUMBER[Straight]},      //15
  {07.61 - 00.00, -10.0, GAIN_NUMBER[SlowCurve]},  //16
  {08.95 - 00.15, +1.0, GAIN_NUMBER[Straight]},         //17
  {09.69 - 00.00, -10.0, GAIN_NUMBER[Curve]},     //18
  {11.17 - 00.15, +1.0, GAIN_NUMBER[Straight]},         //19
  {11.43 - 00.00, -10.0, GAIN_NUMBER[SlowCurve]},     //20
  {12.58 - 00.15, +1.0, GAIN_NUMBER[Straight]},         //21
  {12.89 - 00.00, -10.0, GAIN_NUMBER[Curve]},     //22
  {13.74 - 00.15, +1.0, GAIN_NUMBER[Straight]},         //23
  {13.87 - 00.00, -10.0, GAIN_NUMBER[Curve]},     //24
  {15.16 - 00.00, +1.0, GAIN_NUMBER[FastCurve]},         //25
  {15.70 - 00.15, +1.0, GAIN_NUMBER[Straight]},    //26
  {15.85 - 00.00, -10.0, GAIN_NUMBER[SlowCurve]},     //27
  {16.65 - 00.15, +1.0, GAIN_NUMBER[Straight]},     //28
  {16.85 - 00.00, -10.0, GAIN_NUMBER[SlowCurve]},     //29
  {17.91 - 00.15, +1.0, GAIN_NUMBER[Straight]},         //30
  {18.15 - 00.00, -10.0, GAIN_NUMBER[SlowCurve]},     //31
  {20.97 - 00.15, +1.0, GAIN_NUMBER[Straight]},         //32
  {21.24 - 00.00, -10.0, GAIN_NUMBER[Curve]},     //33
  // {21.73 - 00.15, -10, GAIN_NUMBER[Straight]},         //34
  {FINAL_TARGET_POSITION, +1.0, GAIN_NUMBER[Straight]}
  // {FINAL_TARGET_POSITION-0.2, -10.0, Stop} // 21 End Track
};



#endif
