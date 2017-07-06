#include "QEI.h"
#include "Motor.h"
#include "QTRSensors.h"
#include "PID.h"
#include "_config.h"

PID m1controller(1.0, 0.0, 0.0, 0.01);
PID m2controller(1.0, 0.0, 0.0, 0.01);

PID linecontroller(1.0, 0.0, 0.0, 0.01);

Timer pidtimer;
Timer xtimer;

Serial PC(USBTX, USBRX);

QEI enc1 (PIN_ENC1_A, PIN_ENC1_B, NC, PULSES_PER_REV);
QEI enc2 (PIN_ENC2_A, PIN_ENC2_B, NC, PULSES_PER_REV);

Motor m1(PIN_M1_EN, PIN_M1_IN1, PIN_M1_IN2);
Motor m2(PIN_M2_EN, PIN_M2_IN1, PIN_M2_IN2);

// Line Reader
PinName pinslinereader[6] = {
    PIN_LR_S0,
    PIN_LR_S1,
    PIN_LR_S2,
    PIN_LR_S3,
    PIN_LR_S4,
    PIN_LR_S5
};

DigitalOut led1(LED1);

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog linereader(pinslinereader,
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorvalues[NUM_SENSORS];

void setup() {
    PC.baud(SERIAL_SPEED);
    PC.printf("%s ", PROJECT_NAME); PC.printf("%s\n", PROJECT_VERSION);

    m1controller.setInputLimits(0, 40);
    m1controller.setOutputLimits(0, 1.0);
    //  m1controller.setBias(0.3);
    m1controller.setMode(1);
    //We want the process variable to be 1.7V
//    m1controller.setSetPoint(20);

    m2controller.setInputLimits(0, 40);
    m2controller.setOutputLimits(0, 1.0);
    m2controller.setMode(1);

    linecontroller.setInputLimits(0, 5000);
    linecontroller.setOutputLimits(0, 1.0);
    linecontroller.setMode(1);
    m2controller.setSetPoint(2500);

    m1.brake();
    m2.brake();

}


void lineReaderCalibrate(){
    led1 = 1;
    for (int i = 0; i < 400; i++)
        linereader.calibrate();
    led1 = 0;

    for (int i = 0; i < NUM_SENSORS; i++)
        PC.printf("%4u \t", linereader.calibratedMinimumOn[i]);

    PC.printf("%c", '\n');

    for (int i = 0; i < NUM_SENSORS; i++)
        PC.printf("%4u \t", linereader.calibratedMaximumOn[i]);

    PC.printf("%c", '\n');
    PC.printf("%c", '\n');
}

int main() {

    setup();

    m1controller.setSetPoint(5);
    m2controller.setSetPoint(5);

    enc1.reset();
    enc2.reset();

    pidtimer.start();
    xtimer.start();

    while(1) {

        if (xtimer.read() >= 2) {
            m1.brake();
            m2.brake();
            while(1);
        }
//        else if (xtimer.read() >= 8) {
//            m1controller.setSetPoint(60);
//            m2controller.setSetPoint(60);
//        } else if (xtimer.read() >= 6) {
//            m1controller.setSetPoint(40);
//            m2controller.setSetPoint(40);
//        } else if (xtimer.read() >= 4) {
//            m1controller.setSetPoint(30);
//            m2controller.setSetPoint(30);
//        }
        else if (xtimer.read() >= 0) {
            m1controller.setSetPoint(25);
            m2controller.setSetPoint(25);
        }

        float timeelapsed = pidtimer.read();

        if (timeelapsed >= 0.01) {

            pidtimer.reset();

            unsigned int pulses1 = enc1.getPulses();
            unsigned int pulses2 = enc2.getPulses();

            enc1.reset();
            enc2.reset();

            m1controller.setProcessValue(pulses1);
            m2controller.setProcessValue(pulses2);

            float m1speed = m1controller.compute();
            float m2speed = m2controller.compute();

            m1.speed(m1speed);
            m2.speed(m2speed);

            PC.printf("%.3f ", timeelapsed);

            PC.printf("%.3i ", pulses1);
//            PC.printf("%i ", pulses2);

            PC.printf("%.3f", m1speed);
//            PC.printf("%.3f ", m2speed);

            PC.printf("\n");
        }

//        wait(0.1);
//        PC.printf("Pulses A: %i ", enc1.getPulses());
//        PC.printf("Pulses B: %i\n", enc2.getPulses());

//        unsigned int position = linereader.readLine(sensorvalues);
//
//        for (unsigned char i = 0; i < NUM_SENSORS; i++)
//            PC.printf("%4u \t", sensorvalues[i]);
//        PC.printf("%4u \n", position);
    }

}
