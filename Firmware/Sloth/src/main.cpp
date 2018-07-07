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
Timer cps_left_led_timer; // Acceleration interval
Timer cps_right_led_timer; // Acceleration interval

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
float linePosition; // line position in the line reader

// Lap sensor settings
InterruptIn CheckpointSensorRight(PIN_TRACK_MARKING_RIGHT);
InterruptIn CheckpointSensorLeft(PIN_TRACK_MARKING_LEFT);

// Counters of left and Right sensors
int checkpoint_left_counter = 0;
int checkpoint_right_counter = 0;
int last_checkpoint_left_counter = 0;
int last_checkpoint_right_counter = 0;
int crossroad_counter = 0;

bool robotstate = true;
bool readyStatus = true;
bool motorsEnable=true;

//PID
float directiongain = 0.0;
PID directioncontrol(0, 0, 0);


// float speedbase = 0.30;
// float kpdir = 0.00020;
// float kidir = 0.000000;
// float kddir = 0.0000035;

float speedbase = 0.3;
float kpdir = 0.75;
float kidir = 0.0000000;
float kddir = 0.025;

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

  PC.printf("%s", "Calibrating sensors...");
  BT.printf("%s", "Calibrating sensors...");
  leds[0] = 1;
  for (int i = 0; i < 1000; i++)
    LineReader.calibrate(true);
  leds[0] = 0;
  BT.printf("%s\n", "Done.");
  PC.printf("%s\n", "Done.");
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
      kpdir += 0.00005;
      break;
    case 'B':
      kpdir -= 0.00005;
      break;
    case 'C':
      kidir += 0.0000001;
      break;
    case 'D':
      kidir -= 0.0000001;
      break;
    case 'E':
      kddir += 0.000005;
      break;
    case 'F':
      kddir -= 0.000005;
      break;
    case 'u':
      speedbase += 0.01;
      break;
    case 'd':
      speedbase -= 0.01;
      break;
    // case 'S':
    //   robotstate = false;
    //   break;
    case 'J':
      PC.printf("Encoder Right Now: %.0f \n", currentPosition);
      BT.printf("Encoder Right Now: %.0f \n", currentPosition);
      break;
    case 'G':
      robotstate = true;
      // robotstate = true;
      PC.printf("Robot will Start in 2s");
      BT.printf("Robot will Start in 2s");
      LeftEncoder.reset();
      RightEncoder.reset();
      wait(2);
      break;
    case 'S':
      robotstate = false;
      // robotstate = true;
      PC.printf("Robot Paused");
      BT.printf("Robot Paused");
      break;
    case 'M':
      motorsEnable = !motorsEnable;
      // robotstate = true;
      PC.printf("Motors state changed");
      BT.printf("Motors state changed");
      break;
  }
   directioncontrol.setTunings(kpdir, kidir, kddir);
   BT.printf("%.8f %.8f %.2f\n", kpdir, kddir, speedbase);
}

// Interrupt when Mark Left was change
void checkpointSensorLeftCallback() {
    checkpoint_left_counter++;
    cps_left_led_timer.start();
    leds[0] = 1;
}

//Interrupt when Mark Right was change
void checkpointSensorRightCallback() {
    checkpoint_right_counter++;
    cps_right_led_timer.start();
    leds[3] = 1;
}

int main() {

  // Setup Serial and Welcome message
  PC.baud(PC_SPEED);
  BT.baud(BT_SPEED);
  BT.attach(&btcallback);
  BT.printf("%s ", PROJECT_NAME); LOG.printf("%s\n", PROJECT_VERSION);
  PC.printf("%s ", PROJECT_NAME); LOG.printf("%s\n", PROJECT_VERSION);

  // Release motors for make more easy the calibration
  LeftMotor.coast();
  RightMotor.coast();

  // Calibrate the line sensor
  wait(2);
  lineReaderCalibrate();
  wait(4);

  // Reset Encoders
  LeftEncoder.reset();
  RightEncoder.reset();

  // Activating Interrupt in fall for the Mark Sensors
  CheckpointSensorRight.fall(&checkpointSensorRightCallback);
  CheckpointSensorLeft.fall(&checkpointSensorLeftCallback);

  // Clear mark sensors counters
  checkpoint_left_counter = 0;
  checkpoint_right_counter = 0;

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

    if (checkpoint_right_counter == 0) {
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
    //   CheckpointSensorRight.disable_irq();

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
      float mediumspeed = currentPosition / laptime;
      BT.printf("Time Lap: %.5f\t", laptime);
      BT.printf("Track Length: %.2fm\t ", currentPosition);
      BT.printf("Medium Speed: %.2fm/s\t ",  mediumspeed);
      BT.printf("%s\n", "");

      PC.printf("Time Lap: %.5f\t", laptime);
      PC.printf("Track Length: %.2fm\t ", currentPosition);
      PC.printf("Medium Speed: %.2fm/s\t ",  mediumspeed);
      PC.printf("%s\n", "");

      // Blink the LEDs
      while (!robotstate) {
        for (int i = 0; i <= 3; i++) {
          for (int j = 0; j <= 3; j++) {
            leds[j] = j == i;
            wait(.050);
          }
        }
      }
    }

    else if (robotstate) { // Follow the Line

      //LEDS turn off - About Interrupt
      if (cps_left_led_timer.read() > 0.150) {
        leds[0] = 0;
        cps_left_led_timer.reset();
        cps_left_led_timer.stop();
      }

      if (cps_right_led_timer.read() > 0.150) {
        leds[3] = 0;
        cps_right_led_timer.reset();
        cps_right_led_timer.stop();
      }


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
      linePosition = (float)(LineReader.readLine(sensorvalues, QTR_EMITTERS_ON, WHITE_LINE) - 2500.0)/2500.0;

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
      if(motorsEnable){
        LeftMotor.speed(leftmotorspeed);
        RightMotor.speed(righmotorspeed);
      }

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
      // LOG.printf("%.2f,", LapTimer.read());
      // LOG.printf("%i,", currentMark);
      LOG.printf("%.5f", linePosition);

      // LOG.printf("%.4f,", currentPosition);
      // LOG.printf("%.4f", DIF(leftDistance, rightDistance));
/*
      // Checkpoint sensors mapping
      // Crossroad
      if (checkpoint_left_counter != last_checkpoint_left_counter && checkpoint_right_counter != last_checkpoint_right_counter) {
        crossroad_counter++;
        LOG.printf("%s,%i,", "C", crossroad_counter);
        checkpoint_left_counter--;
        checkpoint_right_counter--;
      }
      // Curve start/end marks
      else if (checkpoint_left_counter != last_checkpoint_left_counter && checkpoint_right_counter == last_checkpoint_right_counter) {
        LOG.printf("%s,%i,", "L", checkpoint_left_counter);
        last_checkpoint_left_counter = checkpoint_left_counter;
      }
      // Start/Finish marks
      else if (checkpoint_left_counter == last_checkpoint_left_counter && checkpoint_right_counter != last_checkpoint_right_counter) {
        LOG.printf("%s,%i,", "R", checkpoint_right_counter);
        last_checkpoint_right_counter = checkpoint_right_counter;
      }
      else {
        LOG.printf("%s", "-,-,");
      }

      // Encoders positions
      LOG.printf("%.2f,", leftDistance);
      LOG.printf("%.2f", rightDistance);
*/

      // LOG.printf("%i", checkpoint_right_counter);
      //Test of Mapping
      // LOG.printf("CurrentPosition: %.2f \t", currentPosition);
      // LOG.printf("CurrentSpeed: %.2f \t", TargetMark.setup.speed);

      LOG.printf("%s","\n");
      LogTimer.reset();
    }
  }

}
