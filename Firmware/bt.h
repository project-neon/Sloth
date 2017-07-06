#include "mbed.h"
#include "MODSERIAL.h"
#include "_config.h"
#include "_types.h"


#ifndef BT_H
#define BT_H

MODSERIAL bluetooth(PIN_TX, PIN_RX);          // TX, RX

class BT{
public:

    // Initialize pins
    static void init();


    static bool checkIsReadable();

    static bool checkIsWriteable();

    static void txCallback(MODSERIAL_IRQ_INFO *q);

    static void rxCallback(MODSERIAL_IRQ_INFO *q);

    static void txEmpty(MODSERIAL_IRQ_INFO *q);
    
    static int main();
};

#endif
