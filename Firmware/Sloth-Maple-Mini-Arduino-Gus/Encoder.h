#include <arduino.h>
#ifndef Encoder_h
#define Encoder_h



class Encoder {
   public:
       Encoder(uint8_t pinA, uint8_t pinB, int pulserPerRev, float wheelRadius);
       float getDistance(); //return distance in meters
       int getPulses();
       float getRevolutions();
       void reset();
       // int _pulses;
       // uint8_t _pinA;
       // uint8_t _pinB;

        // void encoderChannelA();
        // void encoderChannelB();

   protected:
   // int _pulses=0;
   // uint8_t _pinA;
   // uint8_t _pinB;
       int _pulsesPerRev;
       float _revolutions;
       float _distance;
       float _wheelRadius;
};

#endif
