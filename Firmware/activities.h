//this class will have the motors configuration, monitoration and control
#include "mbed.h"

#include "_config.h"
#include "_types.h"

//#include "robot.h"

#ifndef ACTIVITIES_H
#define ACTIVITIES_H

InterruptIn lapRight(PIN_TRACK_MARKING_RIGHT);


class Activities{
public:


    static void init();


    static void


    static void stop();
};

#endif
