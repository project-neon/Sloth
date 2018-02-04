#ifndef PID_H
#define PID_H

#include "mbed.h"
#include "Timer.h"

class PID {
public:

    PID(float kP, float kI, float kD){
        this->kP = kP;
        this->kI = kI;
        this->kD = kD;
        t.start();
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
        
        float deltaTime = t.read(); 
        
        t.reset();
        
        P = error * kP;
        I += (error * kI) * deltaTime;
        D = ((lastSample - sample) * kD) / deltaTime;

        lastSample = sample;
        
        pid = P + I + D;
        
        return pid;
     }
     
     protected: 
        Timer t;
        float error;
        float sample;
        float lastSample;
        float kP, kI, kD;      
        float P, I, D;
        float pid;
        float setPoint;
};

#endif