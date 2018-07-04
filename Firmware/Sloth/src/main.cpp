#include "Motor.h"
#include "QTRSensors.h"
#include "PID.h"
#include "QEI.h"
#include "_config.h"
#include "tracks.h"
// #include "settingsSpeed.h"


// Timers
Timer LogTimer; // Debug the loop
Timer LapTimer; // Time of a lap
Timer AccTimer; // Acceleration interval

// Serial
//Control the Communication with a Computer (Serial) and HC-05
Serial PC(USBTX, USBRX);
Serial BT(BTRX, BTTX);

// Leds
DigitalOut leds[4] = {
    LED1,
    LED2,
    LED3,
    LED4
};

// Motors
Motor LeftMotor(PIN_M1_EN, PIN_M1_IN1, PIN_M1_IN2); // Lefut Motor
Motor RightMotor(PIN_M2_EN, PIN_M2_IN1, PIN_M2_IN2); // Right Motor
float leftmotorspeed = 0.0;
float righmotorspeed = 0.0;
float currentSpeed = 0.0;
float targetSpeed = 0.0;
float acceleration = 0.0;

// Encoders
QEI LeftEncoder (PIN_ENC1_A, PIN_ENC1_B, NC, PULSES_PER_REV); // Left Encoder
QEI RightEncoder (PIN_ENC2_A, PIN_ENC2_B, NC, PULSES_PER_REV); // Right Encoder
float currentPosition; // Robot current position in the track
float leftDistance; // left distance by encoder (m)
float rightDistance; // right distance by encoder (m)

bool firstMarkDone = false;

float POSITION_FIX = 0; //Robot constante to fix the position.

// Line Reader
PinName pinsLineReader[NUM_SENSORS] = {
    PIN_LR_S0, // Most Left Sensor
    PIN_LR_S1,
    PIN_LR_S2,
    PIN_LR_S3,
    PIN_LR_S4,
    PIN_LR_S5 // Most Right Sensor
};
QTRSensorsAnalog LineReader(pinsLineReader,
    NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorvalues[NUM_SENSORS];
int linePosition; // line position in the line reader

// Lap sensor settings
InterruptIn Marksensor1(PIN_TRACK_MARKING_LEFT);
InterruptIn Marksensor2(PIN_TRACK_MARKING_RIGHT);
  // DigitalIn MarksensorTest(PIN_TRACK_MARKING_LEFT);

// Counters of left and Right sensors
bool ms1state = false;
bool ms2state = false;
int ms1count = 0;
int ms2count = 0;
bool robotstate = true;
bool readyStatus = true;

//PID
float directiongain = 0.0;
PID directioncontrol(0, 0, 0);

// Robot Setups
// struct Setup {
//   float speed;
//   float kp;
//   float ki;
//   float kd;
// };

// Robot Standard Setups
                // Speed,   kP,   kI,   kD
// Setup Curve     = {0.85, 0.00030, 0.0000000, 0.0000075};

/* MOTOR 10:1
Setup SlowCurve = {0.3, 0.0020000, 0.000000, 0.000200};

Setup Curve     = {0.4, 0.00020000, 0.000000, 0.000020};

Setup Straight  = {1.0, 0.00030000, 0.000000, 0.00001};
Setup FastCurve     = {0.4, 0.00020000, 0.000000, 0.000020};

Setup Stop      = {0.1, 0.000100, 0, 0.000001};
*/

// MOTOR 30:1
// Setup SlowCurve = {0.62, 0.00025000, 0.000000, 0.0000050};
//
// Setup Curve     = {0.6, 0.00022, 0.000000, 0.0000050};
//
// Setup Straight  = {1.0, 0.00018, 0.000000, 0.0000075};
//
// Setup FastCurve = {0.7, 0.00022, 0.000000, 0.0000075};
// Setup FastFastCurve = {0.95, 0.00022, 0.000000, 0.0000075};
//
// Setup Stop      = {0.1, 0.000100, 0, 0.000001};


float speedbase = 0.35;
float kpdir = 0.00020;
float kidir = 0.000000;
float kddir = 0.0000035;

Setup Normal     = {speedbase, kpdir, kidir, kddir};

void setRobotSetup(Setup setup) {
  // Setup PID and Speed
  targetSpeed = setup.speed;
  directioncontrol.setTunings(setup.kp, setup.ki, setup.kd);
  // If line position is 0, the robot is just over the line
  directioncontrol.setSetPoint(0);
}

// The target mark
Mark TargetMark;
int currentMark = 0;

// Function to calibrate the line reader
void lineReaderCalibrate() {

  LOG.printf("%s", "Calibrating sensors...");
  leds[0] = 1;
  for (int i = 0; i < 500; i++)
    LineReader.calibrate(true);
  leds[0] = 0;
  LOG.printf("%s\n", "Done.");
  //
  // for (int i = 0; i < NUM_SENSORS; i++)
  //   LOG.printf("Min: %4i \t", LineReader.calibratedMinimumOn[i]);
  //
  // LOG.printf("%s", "\n");
  //
  // for (int i = 0; i < NUM_SENSORS; i++)
  //   LOG.printf("Max: %4i \t", LineReader.calibratedMaximumOn[i]);

  // LOG.printf("%s", "\n");
  // LOG.printf("%s", "\n");
}

void btcallback() {
  char rcvd = BT.getc();
  switch (rcvd) {
    case 'A':
      kpdir += 0.01;
      break;
    case 'B':
      kpdir -= 0.01;
      break;
    case 'C':
      kidir += 0.0000001;
      break;
    case 'D':
      kidir -= 0.0000001;
      break;
    case 'E':
      kddir += 0.000001;
      break;
    case 'F':
      kddir -= 0.000001;
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
    case 'J':
      LOG.printf("Encoder Right Now: %.0f \n", currentPosition);
      break;
    case 'K':
      readyStatus = true;
      // robotstate = true;
      LOG.printf("Robot will Start in 2s");
      wait(2);
      break;
    case 'L':
      readyStatus = false;
      // robotstate = true;
      LOG.printf("Robot Paused");
      break;
  }
   directioncontrol.setTunings(kpdir, kidir, kddir);
   // BT.printf("%.8f %.8f %.2f\n", kpdir, kddir, speedbase);
}

// Interrupt when Mark Left was change
void ms1() {
    if (currentMark == 0 && firstMarkDone == false){
      // POSITION_FIX = FIRST_MARK_POSITION - currentPosition;
      // firstMarkDone = true;
    }
    ms1count++;
    leds[2] = true;
}

//Interrupt when Mark Right was change
void ms2() {
    ms2count++;
    leds[3] = true;
}

int main() {

  // Setup Serial and Welcome message
  PC.baud(PC_SPEED);
  BT.baud(BT_SPEED);
  BT.attach(&btcallback);
  LOG.printf("%s ", PROJECT_NAME); LOG.printf("%s\n", PROJECT_VERSION);

  // Activating Interrupt in fall for the Mark Sensors
  // Marksensor2.fall(&ms2); //Sensor Right
  Marksensor1.fall(&ms1); //Sensor Left

  // Release motors for make more easy the calibration
  LeftMotor.coast();
  RightMotor.coast();

  // Calibrate the line sensor
  wait(2);
  lineReaderCalibrate();
  LOG.printf("%s\n", "Sensors Calibrated");
  wait(4);

  // Reset Encoders
  LeftEncoder.reset();
  RightEncoder.reset();

  // Clear mark sensors counters
  ms1count = 0;
  ms2count = 0;

  // Start Timers
  LogTimer.start();
  LapTimer.start();
  AccTimer.start();

  // Set the first setup of the Robot
  if(MAPPING_ENABLED){
    // Get first target mark - 0
    TargetMark = TRACK_EVENT_NAME[currentMark];
    acceleration = TargetMark.acceleration;
    // Update Robot Setup
    setRobotSetup(TargetMark.setup);
  } else {
    // Get first target mark - 0
    TargetMark = TRACK_EVENT_NAME[currentMark];
    acceleration = TargetMark.acceleration;
    // Update Robot Setup
    setRobotSetup(Normal);
  }
  // Main Loop
  while(1) {

    // Get currrent position by encoders and convert to meters

    if (ms1count == 0) {
      LeftEncoder.reset();
      RightEncoder.reset();
    }

    leftDistance = PULSES2DISTANCE(LeftEncoder.getPulses());
    rightDistance = PULSES2DISTANCE(RightEncoder.getPulses());
    currentPosition = AVG(leftDistance, rightDistance) + POSITION_FIX; //get average

    // Check if the robot complete the track
    if (currentPosition >= FINAL_TARGET_POSITION && STOP_BY_DISTANCE) {
      robotstate = false; // Stop the Robot
    }

    // Checks if medium lap time has been reached
    if (LapTimer.read() > LAP_TIME && STOP_BY_TIME) {
      LapTimer.stop();
      robotstate = false; // Stop the robot
    }

    // if (currentMark>0)
    //   Marksensor1.disable_irq();

    if (!robotstate) { // Stop the Robot
      // Stop the robot and release the motors after
      LeftMotor.brake();
      RightMotor.brake();
      wait(.500);
      LeftMotor.coast();
      RightMotor.coast();

      // Stop the Lap Timer
      LapTimer.stop();

      // Print some data for statistics
      float laptime = LapTimer.read();
      // float tracklength = (currentPosition / PULSES_PER_REV) * WHEEL_PERIMETER;
      float mediumspeed = currentPosition / laptime;
      LOG.printf("Time Lap: %.5f\t", laptime);
      LOG.printf("Track Length: %.2fm\t ", currentPosition);
      LOG.printf("Medium Speed: %.2fm/s\t ",  mediumspeed);
      LOG.printf("%s\n", "");

      // Blink the LEDs
      while (1) {
        for (int i = 0; i <= 3; i++) {
          for (int j = 0; j <= 3; j++) {
            leds[j] = j == i;
            wait(.050);
          }
        }
      }
    }

    else if (robotstate && readyStatus) { // Follow the Line

      //LEDS turn off - About Interrupt
      leds[2]=0;
      leds[3]=0;

      // Check if changed mark
      if (currentPosition >= TargetMark.position && MAPPING_ENABLED) {
        currentMark++;
        // Get current Target Mark
        TargetMark = TRACK_EVENT_NAME[currentMark];
        acceleration = TargetMark.acceleration;
        // Update Robot Setup
        setRobotSetup(TargetMark.setup);
      }

      // Position of the line: (left)-2500 to 2500(right)
      linePosition = LineReader.readLine(sensorvalues, QTR_EMITTERS_ON, WHITE_LINE) - 2500.0;

      directioncontrol.setProcessValue(linePosition);
      directiongain = directioncontrol.compute();

      // Speed update with acceleration
      if (ACCELERATION_ENABLED) {
        if (AccTimer.read() > ACCELERATION_INTERVAL) {
          // check if the robot accelerates or decelerates
          if ((acceleration > 0 && currentSpeed < targetSpeed) || (acceleration < 0 && currentSpeed > targetSpeed)) {
            currentSpeed += acceleration * ACCELERATION_INTERVAL;
            currentSpeed = currentSpeed > targetSpeed ? targetSpeed : currentSpeed < 0.0 ? 0.0 : currentSpeed;
            AccTimer.reset();
          }
        }
      } else {
        currentSpeed = targetSpeed;
      }

      // Set the Direction
      leftmotorspeed = currentSpeed + (directiongain > 0 ? -directiongain : 0);
      righmotorspeed = currentSpeed + (directiongain < 0 ? +directiongain : 0);

      // Constrain the speed value to [0.0, 1.0] interval
      leftmotorspeed = leftmotorspeed > 1.0 ? 1.0 : leftmotorspeed < -REVERSE ? -REVERSE : leftmotorspeed;
      righmotorspeed = righmotorspeed > 1.0 ? 1.0 : righmotorspeed < -REVERSE ? -REVERSE : righmotorspeed;

      // LOG.printf("PID is working? %f \n", directiongain);
      LeftMotor.speed(leftmotorspeed);
      RightMotor.speed(righmotorspeed);

    // Test Motors
      // LeftMotor.speed(0.5);
      // RightMotor.speed(0.5);
      // wait(2);
      // LeftMotor.brake();
      // RightMotor.brake();
      // wait(2);
      // LeftMotor.speed(-0.5);
      // RightMotor.speed(-0.5);
      // wait(2);
      // LeftMotor.brake();
      // RightMotor.brake();
      // wait(2);
    }

    if (LogTimer.read() > LOG_INTERVAL && LOG_ENABLED) {
      // LOG.printf("%i\t", currentPosition);
      // LOG.printf("%i\t", TargetMark.position);
      // LOG.printf("%i\t", currentMark);

      // Certifies correct operation of line sensors
      // LineReader.read(sensorvalues, QTR_EMITTERS_ON);
      //  for (int i = 0; i < 6; i++)
      //   LOG.printf("%i \t", sensorvalues[i]);
      // LOG.printf("Line: %i \t", linePosition);

      // LOG.printf("Mark: %i \t", MarksensorTest.read());


     // Certifies correct operation of encoders
     // LOG.printf("Left Encoder: %i \t", LeftEncoder.getPulses());
     // LOG.printf("Right Encoder: %i \t", RightEncoder.getPulses());
     // LOG.printf("%.4f\t", leftDistance);
     // LOG.printf("%.4f\t", rightDistance);

     // Certifies correct operation of motors
     // LOG.printf("PID is working? %f \n", directiongain);
     // LOG.printf("%.2f\t", leftmotorspeed);
     // LOG.printf("%.2f\t", righmotorspeed);

      // Manual Track Mapping
      LOG.printf("%.2f,", LapTimer.read());
      LOG.printf("%i,", linePosition);
      LOG.printf("%.4f,", currentPosition);
      LOG.printf("%.4f,", DIF(leftDistance, rightDistance));
      LOG.printf("%i", ms1count);

      //Test of Mapping
      // LOG.printf("CurrentPosition: %.2f \t", currentPosition);
      // LOG.printf("CurrentMark: %i \t", currentMark);
      // LOG.printf("CurrentSpeed: %.2f \t", TargetMark.setup.speed);

      LOG.printf("%s\n","");
      LogTimer.reset();
    }
  }

}
