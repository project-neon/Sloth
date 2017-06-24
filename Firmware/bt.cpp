#include "mbed.h"
#include "MODSERIAL.h"
#include "_config.h"
#include "_types.h"

bool  isReadable;
bool  isWriteable;

void BT::init(){
    bluetooth.baud(SERIAL_SPEED);
}

bool BT::checkIsReadable(){
  isReadable = false;
  if(bluetooth.readable()){
    isReadable = true;
    printf("%s\n",bluetooth.getc());
  }
  return isReadable;

}

bool BT::checkIsWriteable(){
  return isWriteable;
  if(bluetooth.writeable()){
    isWriteable = true;
    bluetooth.printf ("%s \n", "Hello");
  }
  isWriteable = false;
}
