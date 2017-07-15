#include "Motor.h"
#include "QTRSensors.h"
#include "PID.h"
#include "QEI.h"
#include "_config.h"

// Timers
Timer tbt;
Timer tlap;
Timer tstop;
Timer tsafeline;

Timer taceleration;

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

// Motors
Motor m1(PIN_M1_EN, PIN_M1_IN1, PIN_M1_IN2); // Left Motor
Motor m2(PIN_M2_EN, PIN_M2_IN1, PIN_M2_IN2); // Right Motor
float m1speed = 0.0;
float m2speed = 0.0;

// Encoders
QEI enc1 (PIN_ENC1_A, PIN_ENC1_B, NC, PULSES_PER_REV); // Left Encoder
QEI enc2 (PIN_ENC2_A, PIN_ENC2_B, NC, PULSES_PER_REV); // Right Encoder

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

bool ms1state = false;
bool ms2state = false;
int ms1count = 0;
int ms2count = 0;
bool robotstate = true;

// PIDs
// SPEED: 0.5; KP: 0.00025; KI: 0.0; KD:0.000005; BAT: 7.76
//
// float kpdir = 0.0004;      nota 8 com 8.25V
// float kidir = 0.00000;
// float kddir = 0.0000045;

//Nota 9 TOTAL ESTAVEL COM O PEZINHO 8.25V 26 segundos
// speed = .53
// kp 0.0004
// kd 0.0000045

// 21 segundos Meio Estavel, apenas nas curvas (7) 8.14V
// float speedbase = .62;
// float kpdir = 0.00051;
// float kidir = 0.00000;
// float kddir = 0.0000045;

// 17 segundos Otimo, apenas nas curvas 8.2V
// float speedbase = .62;
// float kpdir = 0.00051;
// float kidir = 0.00000;
// float kddir = 0.0000045;

// ~ 16.9  segudos 8/10 8.24V pequena trepidação nas curvas | Velocidade .80
// float speedbase = .65;
// float kpdir = 0.00057;
// float kidir = 0.00000;
// float kddir = 0.0000048;

float speedbase = .65;
float kpdir = 0.00057;
float kidir = 0.00000;
float kddir = 0.0000048;
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
            robotstate = false;
            break;
    }
    directioncontrol.setTunings(kpdir, kidir, kddir);
    BT.printf("%.8f %.8f %.2f\n", kpdir, kddir, speedbase);
}

void ms1() {
    if (tsafeline > .1) {
      tsafeline.reset();
      ms1state = !ms1state;
      ms1count++;
      leds[1] = true;
      if (ms1count >= CROSS_COUNTER) {
          // robotstate = false;
          tstop.start();
      }
    }
}

// void ms2() {
//     ms2state = !ms1state;
//     ms2count++;
//     if (ms2count >= CROSS_COUNTER)
//         robotstate = false;
// }

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

    marksensor1.fall(&ms1); //Sensor Right

    LOG.printf("%s", "Setup...");
    LOG.printf("%s\n", "Done.");

    // Release motors for make more easy the calibration
    m1.coast();
    m2.coast();

    // Calibrate the line sensor
    wait(1);
    lineReaderCalibrate();
    LOG.printf("%s\n", "Sensores Calibrado");
    wait(2);

//    Reset Encoders
   enc1.reset();
   enc2.reset();

    ms1count = 0;
    ms2count = 0;

//    Start Timers
    tbt.start();
    tsafeline.start();
    tlap.start();
    taceleration.start();

//    Main Loop
    while(1) {

        unsigned int pulses = (enc1.getPulses() + enc2.getPulses()) / 2;
        if (pulses >= NUMBER_PULSES)
          robotstate = false;
          //robotstate = robotstate;

        if (!robotstate) {
            m1.brake();
            m2.brake();
            BT.printf("Time Lap: %.5f\n", tlap.read());
            BT.printf("Pulses: %i %i\n", enc1.getPulses(), enc2.getPulses());
            wait(.250);
            m1.coast();
            m2.coast();

            for (int i = 0; i <= 3; i++) {
            for (int j = 0; j <= 3; j++)
              leds[j] = j == i;
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

            if(tsafeline.read() > .2){
              leds[1] = 0;
            }


            if (tstop.read() > .5) {
              tstop.stop();
              //robotstate = false;
            }

            if(taceleration.read()>1.5)
            {
              speedbase = .60;
              taceleration.stop();
            }
            if (tbt.read() > .001) {

//                LOG.printf("%i ", position);
//                LOG.printf("%.3f ", directiongain);
//                LOG.printf("%.3f ", m1speed);
//                LOG.printf("%.3f ", m2speed);
//                LOG.printf("%.0i ", ms1count);
//                LOG.printf("%.0i\n", ms2count);

                //LOG.printf("%.10f %.10f %.10f %.2f", kpdir, kidir, kddir, speedbase);
                //BT.printf("%.10f %.10f %.10f %.2f", kpdir, kidir, kddir, speedbase);
                // BT.printf("%i",ms.read());
                //LOG.printf("\n");
                // BT.printf("\n");

                tbt.reset();
            }
        }
    }

}
