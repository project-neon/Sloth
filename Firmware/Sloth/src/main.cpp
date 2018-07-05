#include "Motor.h"
#include "QTRSensors.h"
#include "myserial.h"
#include "PID.h"
#include "QEI.h"
#include "_config.h"
#include "tracks.h"

#include <string>
// #include "settingsSpeed.h"


// Timers
Timer LogTimer; // Debug the loop
Timer LapTimer; // Time of a lap
Timer AccTimer; // Acceleration interval

// Serial
//Control the Communication with a Computer (Serial) and HC-05
// Serial PC(USBTX, USBRX);
// Serial BT(BTRX, BTTX);

mySerial BT(BTRX, BTTX);

// char receivedxBuf[RX_MAX];
string receivedxBuf;

int rcvdNow=0;

// Leds
DigitalOut leds[4] = {
    LED1,
    LED2,
    LED3,
    LED4
};

void communicationAction(string rcvd){
  BT.printf("%s\n", rcvd);
}

void btcallback(char id) {
  // while(BT.readable()){
    receivedxBuf = BT.getLine();
  // }

  // // BT.scanf("%s\n", receivedxBuf);
  communicationAction(receivedxBuf);
}

int main() {

  BT.init();
  BT.setAttachRx(&btcallback);
  LOG.printf("%s ", PROJECT_NAME); LOG.printf("%s\n", PROJECT_VERSION);

  // Start Timers
  LogTimer.start();
  LapTimer.start();
  AccTimer.start();

  // Main Loop
  while(1) {

    rcvdNow = 0;
    // Get currrent position by encoders and convert to meters
    // while(BT.readable()){
    //   receivedxBuf = BT.getLine();
    // }

    // BT.scanf("%s\n", receivedxBuf);
    // communicationAction(receivedxBuf);

    if (LogTimer.read() > LOG_INTERVAL && LOG_ENABLED) {
      // LOG.printf("%s\n","");
      LogTimer.reset();
    }
  }

}
