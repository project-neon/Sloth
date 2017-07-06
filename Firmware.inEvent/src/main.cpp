#include "Motor.h"
#include "QTRSensors.h"
#include "PID.h"
//#include "QEI.h"
#include "_config.h"

// Timers
Timer tbt;

// Serial
Serial PC(USBTX, USBRX);
Serial BT(BTRX, BTTX);

// Leds
DigitalOut leds[4] = {
    LED1,
    LED2,
    LED3,
    LED4,
};
bool ms1state;
bool ms2state;

// Motors
Motor m1(PIN_M1_EN, PIN_M1_IN1, PIN_M1_IN2); // Left Motor
Motor m2(PIN_M2_EN, PIN_M2_IN1, PIN_M2_IN2); // Right Motor
float m1speed = 0.0;
float m2speed = 0.0;

// Encoders
//QEI enc1 (PIN_ENC1_A, PIN_ENC1_B, NC, PULSES_PER_REV); // Left Encoder
//QEI enc2 (PIN_ENC2_A, PIN_ENC2_B, NC, PULSES_PER_REV); // Right Encoder

// Line Reader
PinName pinslinereader[NUM_SENSORS] = {
    PIN_LR_S0, // Most Left Sensor
    PIN_LR_S1,
    PIN_LR_S2,
    PIN_LR_S3,
    PIN_LR_S4,
    PIN_LR_S5 // Most Right Sensor
};
QTRSensorsAnalog linereader(pinslinereader,
    NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorvalues[NUM_SENSORS];
int position;

// Lap sensor settings
InterruptIn marksensor1(PIN_TRACK_MARKING_RIGHT);
//InterruptIn marksensor2(PIN_TRACK_MARKING_LEFT);

int ms1count = 0;
int ms2count = 0;
bool robotstate = true;

// PIDs
// SPEED: 0.5; KP: 0.00025; KI: 0.0; KD:0.000005; BAT: 7.76
//
// float kpdir = 0.0004;      nota 8 com 8.25V
// float kidir = 0.00000;
// float kddir = 0.0000045;

float speedbase = .52;
float kpdir = 0.00035;
float kidir = 0.00000;
float kddir = 0.0000040;
float setpointdir = 0.0;
float directiongain = 0.0;
PID directioncontrol(0, 0, 0);

void lineReaderCalibrate(){

    LOG.printf("%s", "Calibrating sensors...");

    leds[0] = 1;
    for (int i = 0; i < 500; i++) {
        linereader.calibrate();
    }
    leds[0] = 0;

    LOG.printf("%s\n", "Done.");

    for (int i = 0; i < NUM_SENSORS; i++)
        LOG.printf("Min: %4i \t", linereader.calibratedMinimumOn[i]);

    LOG.printf("%s", "\n");

    for (int i = 0; i < NUM_SENSORS; i++)
        LOG.printf("Max: %4i \t", linereader.calibratedMaximumOn[i]);

    LOG.printf("%s", "\n");
    LOG.printf("%s", "\n");
}

void btcallback() {
    char rcvd = BT.getc();
    switch (rcvd) {
        case 'A':
            kpdir += 0.00001;
            break;
        case 'B':
            kpdir -= 0.00001;
            break;
        case 'C':
//            kidir += 0.0000001;
            break;
        case 'D':
//            kidir -= 0.0000001;
            break;
        case 'E':
            kddir += 0.0000001;
            break;
        case 'F':
            kddir -= 0.0000001;
            break;
        case 'G':
            speedbase += 0.01;
            break;
        case 'H':
            speedbase -= 0.01;
            break;
        case 'I':
            robotstate = ! robotstate;
            break;
    }
    directioncontrol.setTunings(kpdir, kidir, kddir);
}

void ms1() {
    ms1state = !ms1state;
    ms1count++;
    if (ms1count >= CROSS_COUNTER)
        //robotstate = false;
        robotstate = robotstate;
    LOG.printf("Sensor Rigth Pulse: %4i \t", ms1count);
}

void ms2() {
    ms2state = !ms1state;
    ms2count++;
    if (ms2count >= CROSS_COUNTER)
        robotstate = false;
}

int main() {

//    Setup Serial and Welcome message
    PC.baud(PC_SPEED);
    BT.baud(BT_SPEED);
    BT.attach(&btcallback);
    LOG.printf("%s ", PROJECT_NAME); PC.printf("%s\n", PROJECT_VERSION);
    BT.printf("%s ", PROJECT_NAME); BT.printf("%s\n", PROJECT_VERSION);

//    Setup PID
    directioncontrol.setTunings(kpdir, kidir, kddir);
    directioncontrol.setSetPoint(setpointdir);

     //marksensor1.rise(&ms1); //Sensor Right
     marksensor1.fall(&ms1); //Sensor Right
    // marksensor2.rise(&ms2); // Sensor Left

    LOG.printf("%s", "Setup...");
    LOG.printf("%s\n", "Done.");

    // Release motors for make more easy the calibration
    m1.coast();
    m2.coast();

    wait(1);
    lineReaderCalibrate();
    LOG.printf("%s\n", "Sensores Calibrado");
    wait(2);

//    Reset Encoders
//    enc1.reset();
//    enc2.reset();

    ms1count = 0;
    ms2count = 0;

//    Start Timers
    tbt.start();

//    Main Loop
    while(1) {

        if (!robotstate) {
            m1.brake();
            m2.brake();
            for (int i = 0; i <= 3; i++) {
                for (int j = 0; j <= 3; leds[j++] = j == i);
                wait(.250);
            }
        } else {

            // Position of the line: (left)-2500 to 2500(right)
            position = linereader.readLine(sensorvalues, QTR_EMITTERS_ON, WHITE_LINE) - 2500.0;

            directioncontrol.setProcessValue(position);
            directiongain = directioncontrol.compute();
            m1speed = speedbase + (directiongain > 0 ? -directiongain : 0);
            m2speed = speedbase + (directiongain < 0 ? +directiongain : 0);
            m1.speed(m1speed);
            m2.speed(m2speed);

            if (tbt.read() > .5) {

//                LOG.printf("%i ", position);
//                LOG.printf("%.3f ", directiongain);
//                LOG.printf("%.3f ", m1speed);
//                LOG.printf("%.3f ", m2speed);
//                LOG.printf("%.0i ", ms1count);
//                LOG.printf("%.0i\n", ms2count);

                //LOG.printf("%.10f %.10f %.10f %.2f", kpdir, kidir, kddir, speedbase);
                BT.printf("%.10f %.10f %.10f %.2f", kpdir, kidir, kddir, speedbase);

                //LOG.printf("\n");
                BT.printf("\n");

                tbt.reset();
            }
        }
    }

}
