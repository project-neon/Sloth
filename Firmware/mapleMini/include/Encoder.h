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
        // void encoderChannelA();  
        // void encoderChannelB();  

    protected:
        int _pulsesPerRev;
        float _revolutions;
        float _distance;
        float _wheelRadius;
};

#endif
