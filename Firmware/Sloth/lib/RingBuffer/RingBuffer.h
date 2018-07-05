/**
Ring Buffer reconciled with RTOS.

Default RingBuffer size is 256 Bytes, Max size is 1024 Bytes.
*/

/**
@code
class tmpSerial{
public:
    tmpSerial(PinName TX, PinName RX)
        : serial(TX, RX)
    {
        // attach rxIrq. because, rx buf of serial equals to 16 Bytes.
        this->serial.attach(this, &tmpSerial::_readIrq, Serial::RxIrq);
    }
    string read()
    {
        if(ringBuf.empty())
            return "";
        // rxStr is not empty.
        return ringBuf.get();
    }
private:
    Serial serial;
    RingBuffer ringBuf;
    void _readIrq(void)
    {
        while(serial.readable())
            ringBuf.set(hc05.getc());
        return;
    }
};
@endcode
*/


#include "mbed.h"
#include <string>

#define MaxBufSize     1024
/*
#ifdef RTOS_H
extern Mutex mutex;
#endif
*/
class RingBuffer
{
public:
    // Reccomend 2^n: pow(2,n)
    RingBuffer(unsigned int size= 256);
    ~RingBuffer();

    /** Returned empty status of ringBuffer.
     */
    bool empty();

    /** Returned boolean of find CR(\r)
     */
    bool chkCR();

    /** Set char or string to ring-buffer.
     *  @param;     char or string.
     *  @return;    bool(Buffer FULL: true)
     */
    bool set(char chr);
    bool set(string &str);   // Return Full、参照渡し

    /** Get RingBuffer string.
     *  if this called, RingBuffer is cleared.
     *  @return;    string: buffered string.
     */
    string get();
    char getc();
    string getLine();

private:
    volatile bool _empty;
    unsigned short idxF, idxR;    // front, rear
    char *buf;
    unsigned int bufSize;
    // %
    bool isPowers2;
    bool breakFalg;
    void modulo(unsigned short &idx);
};

// eof
