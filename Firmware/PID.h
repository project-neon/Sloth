#ifndef PID_H
#define PID_H

#include "Arduino.h"

class PID {
public:

    PID(float kP, float kI, float kD){
        this->kP = kP;
        this->kI = kI;
        this->kD = kD;
        lastTimer = 0;
    }
    
    void setProcessValue(float sample){
        this->sample = sample;
    }
    
    void setSetPoint(float setPoint){
        this->setPoint = setPoint;
    }
    
    void setTunings(float kP, float kI, float kD){
        this->kP = kP;
        this->kI = kI;
        this->kD = kD;
    }
    
    float compute(){
        
        error = setPoint - sample;
        timer = millis();
        float deltaTime =  timer - lastTimer;
        lastTimer = timer;
        P = error * kP;
        I += (error * kI) * deltaTime;
        D = ((lastSample - sample) * kD) / deltaTime;

        lastSample = sample;
        
        pid = P + I + D;
        
        return pid;
     }
     
     protected: 
        float timer;
        float lastTimer;
        float error;
        float sample;
        float lastSample;
        float kP, kI, kD;      
        float P, I, D;
        float pid;
        float setPoint;
};

#endif
