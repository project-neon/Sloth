// this class will contain the mais code that's called by the robot
//It will initiate the diferents robot's functions in the propper and logical order
// System Includes
#include "mbed.h"
// Custom Util
#include "_types.h"
#include "_config.h"

// Modules
// #include "imu.h"
#include "PID.h"
#include "robot.h"
#include "motors.h"
//#include "runner.h"
#include "lineReader.h"
#include "bt.h"
//#include "activities.h"
// #include "controller.h"


void configuration(){

  // Initialize Robot state and I/O Pins
  //Robot::init();

  // Initalize Line Sensors
  LineReader::init();

  // Initalize Motors (object)
  Motors::init();

  // Initialize Runner (Manages program execution)
  //Runner::init();
}

// long start, end;
int pos = 0;
void main(){
  // if(Interface::readButton() == STICK_RIGHT){
  //   pos++;
  //   Motors::setSteering(pos);
  //   delay(50);
  // }
  //
  // if(Interface::readButton() == STICK_LEFT){
  //   pos--;
  //   Motors::setSteering(pos);
  //   delay(50);
  // }
  //
  // if(Interface::readButton() == STICK_CENTER){
  //   while(Interface::readButton() != STICK_RELEASED);
  //
  //   Motors::setPower(50, 50);
  //   delay(4000);
  //   Motors::setPower(0, 0);
  // }
  configuration();

  Controller:startFollow();

}
