#include "mbed.h"
#include "MODSERIAL.h"
#include "_config.h"
#include "_types.h"

bool  isReadable;
bool  isWriteable;
bool new_send = false;
bool new_response = false;
bool allClear= false;
char blueChar[80];
char blueReceived[10];

void BT::init(){
    bluetooth.baud(SERIAL_SPEED);
    bluetooth.attach(&txCallback, MODSERIAL::TxIrq);
    bluetooth.attach(&rxCallback, MODSERIAL::RxIrq);
    bluetooth.attach(&txEmpty,    MODSERIAL::TxEmpty);
}

bool BT::checkIsReadable(){
  isReadable = false;
  if(bluetooth.readable()){
    isReadable = true;
  }
  return isReadable;

}

bool BT::checkIsWriteable(){
  isWriteable = false;
  if(bluetooth.writeable()){
    isWriteable = true;
  }
  return isWriteable;
}

// This function is called when a character goes from the TX buffer
void txCallback(MODSERIAL_IRQ_INFO *q) {
    new_send=true;
}
// This function is called when a character goes into the RX buffer.
void rxCallback(MODSERIAL_IRQ_INFO *q) {
    new_response = true;
}
void txEmpty(MODSERIAL_IRQ_INFO *q) {
    allClear = true;
}

char BT::read(){
  if(new_send)
  {
      int i = 0;

      while(bluetooth.readable())
      {
          blueReceived[i] = bluetooth.getc();
          i++;
      }
      new_send = false;
    }
    return blueReceived;
}

void BT::send(char *c){
  int i=0;
  while(c[i] != NULL && bluetooth.writeable())
  {
    bluetooth.putc(c[i]);
    i++;
  }
}

int BT::main(){

}
