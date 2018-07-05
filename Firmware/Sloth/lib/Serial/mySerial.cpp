#include "mySerial.h"

mySerial::mySerial(PinName TX, PinName RX)
    : serial(TX, RX)
{
}
void mySerial::init(int baudrate, int bit, int parity, int stop, bool CRLN)
{
    serial.baud(baudrate);

    // 力技
    if      (parity == SerialBase::Odd)
        serial.format(bit, SerialBase::Odd,  stop);
    else if (parity == SerialBase::Even)
        serial.format(bit, SerialBase::Even, stop);     // 8bit, NonParity, 1stopbit
    else// if (parity == SerialBase::None)
        serial.format(bit, SerialBase::None, stop);     // 8bit, NonParity, 1stopbit

    // attach rxIrq. because, rx buf of serial equals to 16 Bytes.
    this->serial.attach(this, &mySerial::_readIrq, Serial::RxIrq);
    // Tx Buf empty Interrupt.
    this->serial.attach(this, &mySerial::putcIrq, Serial::TxIrq);

    CR= '\r';
    if(CRLN)
        CR= "\r\n";
    return;
}

void mySerial::setAttachRx(void (*fptr)(char))
{
    // Serial.attachから呼ばれる_readIrq()内から、fptrをCall.
    fptrRxIrq= fptr;
    return;
}

bool mySerial::readable()
{
    return serial.readable() || !ringBufRx.empty();
}

string mySerial::get() // public:
{
    _read();
    if(ringBufRx.empty())
        return "";
    return ringBufRx.get();
}

string mySerial::getLine()
{
    /*
        string tmp= this->read();
        if(tmp.empty())
            return "";

        // tmp is not empty.
        int idx= tmp.rfind('\r');
        if(idx == string::npos) {
            ringBufRx.set(tmp);   // 戻す
            return "";
        }
    */

    _read();
    // RingBuf is empty of doesm't find CR.
    if(ringBufRx.empty() || !ringBufRx.chkCR())
        return "";

    return ringBufRx.getLine();
    /*
        string tmp= ringBufRx.get();
        // find \r
        if(tmp[++idx] == '\n')
            idx++;

        // idxは改行後の文字先頭Indexを示す。
        string rtn= tmp.substr(0, idx);
        tmp= tmp.substr(idx);
        ringBufRx.set(tmp);
        return rtn;
    */
}

void mySerial::sendLine(string str, bool addCR)
{
    if(addCR)
        str += "\r\n";
    this->printf(str.c_str());   // _putc()が呼ばれるはず
    return;
}

int mySerial::_putc(int val)     // for printf()
{
    ringBufTx.set(val);
//    serial.putc(val);
    putcIrq();
    return val;
}

int mySerial::_getc()       // for "Stream"
{
    return -1;//mySerial.getc();
}

void mySerial::putcIrq(void)
{
    if(!serial.writeable() || ringBufTx.empty())
        return;
    
    serial.putc(ringBufTx.getc());
    return;
}

// Internal READ()
void mySerial::_readIrq(void)
{
    if(!serial.readable())
        return;

    char chr= serial.getc();
    ringBufRx.set(chr);

    if(this->fptrRxIrq == NULL)
        return;
        
    fptrRxIrq(chr);
    return;
}
void mySerial::_read()
{
    // Bufferを吸い尽くす
    while(serial.readable())
        ringBufRx.set((char)serial.getc());
    return;         // Bufferになくなった
}

// EOF