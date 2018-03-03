#include "Motor.h"
#include "QTRSensors.h"
#include "PID.h"
#include "QEI.h"
#include "_config.h"

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
// InterruptIn Marksensor1(PIN_TRACK_MARKING_RIGHT);
// InterruptIn Marksensor2(PIN_TRACK_MARKING_LEFT);

// bool ms1state = false;
// bool ms2state = false;
// int ms1count = 0;
// int ms2count = 0;
bool robotstate = true;

//PID
float directiongain = 0.0;
PID directioncontrol(0, 0, 0);

// Robot Setups
struct Setup {
  float speed;
  float kp;
  float ki;
  float kd;
};

float highAceleration = 0.1;
float slowAceleration = 0.05;
// Robot Standard Setups
Setup SlowCurve = {0.60, 0.00025, 0, 0.0000050};
// Setup Curve     = {0.60, 0.00045, 0, 0.0000045};
Setup Curve     = {0.70, 0.00025, 0.0000000, 0.0000053};
Setup FastCurve = {0.85, 0.00022, 0, 0.0000060};
Setup Straight  = {1.00, 0.00020, 0, 0.0000075};

void setRobotSetup(Setup setup) {
  // Setup PID and Speed
  targetSpeed = setup.speed;
  directioncontrol.setTunings(setup.kp, setup.ki, setup.kd);
  // If line position is 0, the robot is just over the line
  directioncontrol.setSetPoint(0);
}

// Mark Struct
struct Mark {
  float position; // number of pulses
  float acceleration; // mark acceleration
  Setup setup; // robot setup
};

// Mark Marks[] = { // {Positon, Speed Level}
//   {5.11,  Curve},
//   {6.29, Straight},
//   {7.469, Curve},  // Big Curve Start
//   {8.65, Straight},  // Big Curve End - Double S Start
//   {10.27, SlowCurve},  // Double S End - Straight Start
//   {10.5023, Straight},  // Straight End - S Start
//   {11.794, Curve}, // S Start - Final Straight
//   {FINAL_TARGET_POSITION, Straight} // End Track
// };

Mark Marks[] = { // {Positon, Speed Level}
  {01.90, +1.5, Straight},
  {02.65, -10, Curve},

  {07.30, +0.75, FastCurve},
  {08.10, -10, SlowCurve},

  {08.40, +0.5, Straight},
  {10.40, -10, SlowCurve},

  {11.40, +0.75, Straight},
  {11.90, -10, FastCurve},

  {12.70, +0.75, Straight},
  {13.40, -10, SlowCurve},

  {14.70, +0.75, Straight},
  {15.10, -10, SlowCurve},

  {15.60, +0.75, Straight},
  {16.10, -10, SlowCurve},

  {16.60, +0.75, Straight},
  {17.10, -10, SlowCurve},

  {17.50, +0.75, Straight},
  {18.00, -10, SlowCurve},

  {18.30, +0.75, Straight},
  {19.40, -10, Curve},

  {20.15, +0.75, Straight},
  {FINAL_TARGET_POSITION, +2.5, FastCurve} // End Track
};

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

  for (int i = 0; i < NUM_SENSORS; i++)
    LOG.printf("Min: %4i \t", LineReader.calibratedMinimumOn[i]);

  LOG.printf("%s", "\n");

  for (int i = 0; i < NUM_SENSORS; i++)
    LOG.printf("Max: %4i \t", LineReader.calibratedMaximumOn[i]);

  LOG.printf("%s", "\n");
  LOG.printf("%s", "\n");
}

void btcallback() {
  char rcvd = BT.getc();
  switch (rcvd) {
    // case 'A':
    //   kpdir += 0.00001;
    //   break;
    // case 'B':
    //   kpdir -= 0.00001;
    //   break;
    // case 'C':
    //   kidir += 0.0000001;
    //   break;
    // case 'D':
    //   kidir -= 0.0000001;
    //   break;
    // case 'E':
    //   kddir += 0.0000001;
    //   break;
    // case 'F':
    //   kddir -= 0.0000001;
    //   break;
    case 'G':
      //speedbase += 0.01;
      break;
    case 'H':
      //speedbase -= 0.01;
      break;
    case 'I':
      robotstate = false;
      break;
    case 'J':
      LOG.printf("Encoder Right Now: %.0f \n", currentPosition);
      break;
  }
  // directioncontrol.setTunings(kpdir, kidir, kddir);
  // BT.printf("%.8f %.8f %.2f\n", kpdir, kddir, speedbase);
}

//Interrupt when Mark Left was change
// void ms1() {
//     if (tsafeline > .1) {
//       tsafeline.reset();
//       LapTimer.start();
//       ms1state = !ms1state;
//       ms1count++;
//       leds[1] = true; //Debug in led
//       // Calculate Travelled Distance by encoders
//       if (ms1count >= CROSS_COUNTER) {
//           // robotstate = false;
//           tstop.start();
//       }
//     }
// }

// //Interrupt when Mark Right was change
// void ms2() {
//     ms2state = !ms1state;
//     ms2count++;
//     tsafeline.reset();
//     leds[1] = true;
//     // Calculate Travelled Distance by encoders
//     nowEnc = (LeftEncoder.getPulses() + RightEncoder.getPulses()) / 2;
//     deltaEnc = nowEnc - lastReader_enc;
//     lastReader_enc = nowEnc;
//     BT.printf("Distance: %i %f \n", ms2count, nowEnc);
// }

int main() {

  // Setup Serial and Welcome message
  PC.baud(PC_SPEED);
  BT.baud(BT_SPEED);
  BT.attach(&btcallback);
  LOG.printf("%s ", PROJECT_NAME); LOG.printf("%s\n", PROJECT_VERSION);

  // Activating Interrupt in fall for the Mark Sensors
  // Marksensor1.fall(&ms1); //Sensor Right
  // Marksensor2.fall(&ms2); //Sensor Left

  // Release motors for make more easy the calibration
  LeftMotor.coast();
  RightMotor.coast();

  // Calibrate the line sensor
  wait(1);
  lineReaderCalibrate();
  LOG.printf("%s\n", "Sensors Calibrated");
  wait(2);

  // Reset Encoders
  LeftEncoder.reset();
  RightEncoder.reset();

  // Clear mark sensors counters
  // ms1count = 0;
  // ms2count = 0;

  // Start Timers
  LogTimer.start();
  LapTimer.start();
  AccTimer.start();

  // Set the first setup of the Robot
  if(MAPPING_ENABLED){
    // Get first target mark - 0
    TargetMark = Marks[currentMark];
    acceleration = TargetMark.acceleration;
    // Update Robot Setup
    setRobotSetup(TargetMark.setup);
  } else {
    // Update Robot Setup
    setRobotSetup(Curve);
  }
  // Main Loop
  while(1) {

    // Get currrent position by encoders
    leftDistance = PULSES2DISTANCE(LeftEncoder.getPulses());
    rightDistance = PULSES2DISTANCE(RightEncoder.getPulses());
    currentPosition = AVG(leftDistance, rightDistance);

    // Check if the robot complete the track
    if (currentPosition >= FINAL_TARGET_POSITION && STOP_BY_DISTANCE) {
      robotstate = false; // Stop the Robot
    }

    // Checks if medium lap time has been reached
    if (LapTimer.read() > LAP_TIME && STOP_BY_TIME) {
      LapTimer.stop();
      robotstate = false; // Stop the robot
    }

    if (!robotstate) { // Stop the Robot
      // Stop the robot and release the motors after
      LeftMotor.brake();
      RightMotor.brake();
      wait(.250);
      LeftMotor.coast();
      RightMotor.coast();

      // Stop the Lap Timer
      LapTimer.stop();

      // Print some data for statistics
      float laptime = LapTimer.read();
      float tracklength = (currentPosition / PULSES_PER_REV) * WHEEL_PERIMETER;
      float mediumspeed = tracklength / laptime;
      LOG.printf("Time Lap: %.5f\t", laptime);
      LOG.printf("Track Length: %.2fm\t", tracklength);
      LOG.printf("Medium Speed: %.2fm/s\t",  mediumspeed);

      // Print the robot position only for the first laps
      LOG.printf("Position: %i %i\t", currentPosition);

      LOG.printf("%s\n", "");

      // Blink the LEDs
      while (1) {
        for (int i = 0; i <= 3; i++) {
          for (int j = 0; j <= 3; j++) {
            leds[j] = j == i;
            wait(.250);
          }
        }
      }

    }
    else { // Follow the Line

      // Check if changed mark
      if (currentPosition >= TargetMark.position && MAPPING_ENABLED) {
        currentMark++;
        // Get current Target Mark
        TargetMark = Marks[currentMark];
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
      leftmotorspeed = leftmotorspeed > 1.0 ? 1.0 : leftmotorspeed < 0.0 ? 0.0 : leftmotorspeed;
      righmotorspeed = righmotorspeed > 1.0 ? 1.0 : righmotorspeed < 0.0 ? 0.0 : righmotorspeed;

      // LOG.printf("PID is working? %f \n", directiongain);
      LeftMotor.speed(leftmotorspeed);
      RightMotor.speed(righmotorspeed);
    }

    if (LogTimer.read() > LOG_INTERVAL && LOG_ENABLED) {
      // LOG.printf("%i\t", currentPosition);
      // LOG.printf("%i\t", TargetMark.position);
      // LOG.printf("%i\t", currentMark);

      // LineReader.read(sensorvalues, QTR_EMITTERS_ON);
       //for (int i = 0; i < 6; i++)
        //LOG.printf("%i\t", sensorvalues[i]);
     //LOG.printf("%i", linePosition);
     //LOG.printf("%.4f\t", leftDistance);
     //LOG.printf("%.4f\t", rightDistance);

      // Manual Track Mapping
      // LOG.printf("%.2f\t", LapTimer.read());
      // LOG.printf("%.2f\t", currentPosition);
      // LOG.printf("%.4f\t", DIF(leftDistance, rightDistance));
      // LOG.printf("%s\n","");
      LogTimer.reset();
    }
  }

}
