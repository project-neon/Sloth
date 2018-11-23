/**     Bluetooth module mySerial control class with using RTOS.
 *
 */
/**
 * @code
#include "mbed.h"
#include "mySerial.h"

DigitalOut led[]= {LED1, LED2, LED3, LED4};
mySerial pc(USBTX, USBRX);

void rcvIrq(char id)
{
    led[0]= !led[0];
    if('2'<=id && id<='4') {   // LED2 ~ 4
        id -= '1';
        led[id]= !led[id];
    }
    return;
}

int main()
{
    pc.init();
    pc.setAttachRx(rcvIrq);
    while(true) {
        pc.printf("@");
        pc.sendLine(pc.get());
        wait(10);
    }
}
// EOF
 * @endcode
*/

#pragma once

#include "mbed.h"
#include <string>
#include "RingBuffer.h"

/**     Serial communicate class with Tx & Rx ringbuf.
 *
 */
class mySerial : public Stream
{
public:
    /** Create Serial port to mySerial.
     *  @param TX, RX;              Serial port.
     */
    mySerial(PinName tx, PinName rx);

    /** init
     *  @param baud-rate;           Baud rate (bps). 9600, 38,400, 115,200, 230,400
     *  @param bit, parity, stop;   Default: 1Stopbit, NoneParity, 1StopBit.
     *                              -- parity select; N(None), O(Odd), E(Even).
     *  @param CRLN;                true -> CR&LN (\r\n), false -> CR only (\r).
     */
    void init(int baudrate= 115200, int bit=8, int parity=SerialBase::None, int stop=1, bool CRLN=true);


    void setAttachRx(void (*fptr)(char));
    
    bool readable();
    string get();
    string getLine();
    
    void sendLine(string str, bool addCR=true);

private:
    RawSerial serial;
    string CR;
    RingBuffer ringBufRx;
    RingBuffer ringBufTx;

    // RxIrq function pointer as out of class.
    void (*fptrRxIrq)(char);

    // copy buf of rx to private string.
    void _read();       // copy buf of rx to private string.
    void _readIrq();    // copy buf of rx to private string.

    // virtual func for printf() in Stream-class.
    virtual int _putc(int val);
    virtual int _getc();
    void putcIrq();
};

// EOF