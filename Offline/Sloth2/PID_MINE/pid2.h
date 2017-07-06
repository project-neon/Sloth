//this class will contain all PID logic and processing
#include "_config.h"


#ifndef pid2_H
#define pid2_H
class PID2{
public:

  float desired;     //< set point

    float prevError;    //< previous error
    float integ;        //< integral

    float kp;           //< proportional gain
    float ki;           //< integral gain
    float kd;           //< derivative gain

    float iLimit;       //< integral limit

  PID2(float kp, float ki, float kd, float _ilimit);
  void setSetPoint(float _setPoint);
  float update(float input, float dt);
    void clear();
};

#endif
