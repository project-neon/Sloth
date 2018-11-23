#include "RingBuffer.h"

RingBuffer::RingBuffer(unsigned int size)
{
    _empty= true;
    idxF= idxR= 0;
    // BufSizeの制限は…
    if(size > MaxBufSize)
        size= MaxBufSize;
    buf= new char[size];
    bufSize= size;
    isPowers2= false;
    if( (size & (size- 1)) == 0)
        isPowers2= true;
}
RingBuffer::~RingBuffer()
{
    delete [] buf;
}

bool RingBuffer::empty()
{
    return this->_empty;
}

bool RingBuffer::chkCR()
{
    unsigned short idx= idxF;
    while(true) {
        if(buf[idx] == '\r')
            return true;
        idx++;
        modulo(idx);
        if(idx == idxR)
            return false;
    }

}

bool RingBuffer::set(string &str)
{
    int size= str.size();
    for(int idx= 0; idx < size; idx++)
        if(this->set( (char)str[idx] ))    // True:FULL
            return true;
    return false;
}

bool RingBuffer::set(char chr)
{
    if((idxR == idxF) && !_empty)    // R==F: empty or full
        return true;    // means FULL

    if(chr == NULL)
        return false;

// mutex for RTOS
    /*
    #ifdef RTOS_H
        mutex.lock();
    #endif
    */
    buf[idxR] = chr;
    idxR++;
//    idxR %= bufSize;
    modulo(idxR);
    _empty= false;
    /*
    #ifdef RTOS_H
        mutex.unlock();
    #endif
    */
    if(idxR == idxF)
        return true;
    return false;
}

char RingBuffer::getc()
{
    if(_empty)
        return NULL;

//    string str;
//    int idx= idxF;
//    while(!_empty) {
    char tmp= buf[idxF];
//        idxF++;
//        idxF %= bufSize;
    modulo(++idxF);
    if(idxF == idxR)
        _empty= true;

    return tmp;
}

string RingBuffer::get()
{
    if(_empty)
        return "";

    string str;
//    int idx= idxF;
    while(!_empty) {
        str += buf[idxF];
        idxF++;
//        idxF %= bufSize;
        modulo(idxF);
        if(idxF == idxR)
            _empty= true;
    }
    return str;
}

string RingBuffer::getLine()
{
    if(_empty || !this->chkCR())
        return "";

    string str;
//    int idx= idxF;
    bool breakFlag= false;
    char chr;
    while(!breakFlag) {
        chr= buf[idxF++];
        str += chr;

        modulo(idxF);
        if(idxF == idxR) {
            _empty= true;
            breakFalg= true;
        }

        if(chr == '\r') {
            breakFlag= true;
            if(!_empty && buf[idxF]=='\n') {
                str += buf[idxF++];
                modulo(idxF);
                if(idxF == idxR)
                    _empty= true;
            }
        }
    }
    return str;
}

void RingBuffer::modulo(unsigned short &idx)
{
    if(isPowers2)
        idx= idx & (bufSize-1);
    else
        idx %= bufSize;
    return;
}

//eof
