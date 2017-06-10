#include "mbed.h"
#include "_config.h"
#include "_types.h"

//#include "robot.h"
#include "motors.h"


//// Initialize pins
void Motors::init(){
    pwmM1.period(PWM_PERIOD);
    pwmM2.period(PWM_PERIOD);
    
    Motors::setPower(0, 0);
}


//// Set power of both DC motors
void Motors::setPower(float m1, float m2){

    // Limit Powers
    m1 = min(max(m1, -100.0), 100.0);
    m2 = min(max(m2, -100.0), 100.0);

    // Map powers
    float powerOutA = m1 / 100.0;
    float powerOutB = m2 / 100.0;

    // Set power
    pwmM1.write(powerOutA);
    pwmM2.write(powerOutB);

    // Set Directions
    in1M1 = powerOutA >  0 ? 1 : 0;
    in2M1 = powerOutA >= 0 ? 0 : 1;

    in1M2 = powerOutB >  0 ? 1 : 0;
    in2M2 = powerOutB >= 0 ? 0 : 1;

}

void Motors::stop(){
    // Stop motor 1
    pwmM1.write(0);
    in1M1 = 0;
    in2M1 = 0;

    // Stop motor 2
    pwmM2.write(0);
    in1M2 = 0;
    in2M2 = 0;
}
