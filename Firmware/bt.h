#include "mbed.h"
#include "MODSERIAL.h"
#include "_config.h"
#include "_types.h"


#ifndef BT_H
#define BT_H

Serial bluetooth(PIN_TX, PIN_RX);          // TX, RX

class BT{
public:

    // Initialize pins
    static void init();


    static bool checkIsReadable();

    static bool checkIsWriteable();

    static void send();
};

#endif
