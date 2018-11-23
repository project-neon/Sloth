
#include "Motor.h"
// #include "Encoder.h"
#include "_config.h"
#include "QEI.h"
#include "PID.h"
#include "QTRSensors.h"

#include "tracks.h"

// #include "QTR.h"

Motor LeftMotor(PIN_M1_PWM, PIN_M1_IN1, PIN_M1_IN2);
Motor RightMotor(PIN_M2_PWM, PIN_M2_IN1, PIN_M2_IN2);
int leftmotorspeed = 0;
int righmotorspeed = 0;
int currentSpeed = 0;
int targetSpeed = 0;
int acceleration = 0;

QEI LeftEncoder(PIN_ENC1_A, PIN_ENC1_B, PULSES_PER_REV, WHEEL_RADIUS);
QEI RightEncoder(PIN_ENC2_A, PIN_ENC2_B, PULSES_PER_REV, WHEEL_RADIUS);
float currentPosition; // Robot current position in the track
float leftDistance; // left distance by encoder (m)
float rightDistance; // right distance by encoder (m)
bool firstMarkDone = false;


unsigned char pinsLineReader[NUM_SENSORS] = {
	PIN_LR_S1,
	PIN_LR_S2,
	PIN_LR_S3,
	PIN_LR_S4,
	PIN_LR_S5,
	PIN_LR_S6,
	// PIN_LR_S7,
	// PIN_LR_S8
  };

unsigned int sensorValues[NUM_SENSORS];

QTRSensorsAnalog LineReader(pinsLineReader, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);

// QTR LineReader(pinsLineReader, NUM_SENSORS, EMITTER_PIN);

int linePosition;

// Counters of left and Right sensors
int checkpoint_left_counter = 0;
int checkpoint_right_counter = 0;
int last_checkpoint_left_counter = 0;
int last_checkpoint_right_counter = 0;
int crossroad_counter = 0;

bool robotstate = true;
bool readyStatus = true;

//PID
int directiongain = 0;
PID directioncontrol(0, 0, 0);

// The target mark
Mark TargetMark;
int currentMark = 0;

// Timers
 float startLogTimer; // Debug the loop
 float startLapTimer; // Time of a lap
 float startAccTimer; // Acceleration interval
 float startCps_left_led_timer; // Acceleration interval
 float startCps_right_led_timer; // Acceleration interval

 float nowLogTimer; // Debug the loop
 float nowLapTimer; // Time of a lap
 float nowAccTimer; // Acceleration interval
 float nowCps_left_led_timer; // Acceleration interval
 float nowCps_right_led_timer; // Acceleration interval

// Interrupt when Mark Left was change
void checkpointSensorLeftCallback() {
    checkpoint_left_counter++;
    // cps_left_led_timer.start();
    digitalWrite(PIN_LED,1);
}

//Interrupt when Mark Right was change
void checkpointSensorRightCallback() {
    checkpoint_right_counter++;
    // cps_right_led_timer.start();
    digitalWrite(PIN_LED,1);
}

void setupPID(Setup setup){
  // Setup PID and Speed
  targetSpeed = setup.speed;
  directioncontrol.setTunings(setup.kp, setup.ki, setup.kd);
  // If line position is 0, the robot is just over the line
  directioncontrol.setSetPoint(0);
}

void setupMarkSensors(){
  attachInterrupt(digitalPinToInterrupt(PIN_TRACK_MARKING_RIGHT),checkpointSensorRightCallback, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_TRACK_MARKING_LEFT), checkpointSensorLeftCallback, FALLING);
}

void setupRobot(){


  // Release motors for make more easy the calibration
  LeftMotor.coast();
  RightMotor.coast();

  // Calibrate the line sensor
  setupLineReader();

  // Reset Encoders
  LeftEncoder.reset();
  RightEncoder.reset();

  // Clear mark sensors counters
  checkpoint_left_counter = 0;
  checkpoint_right_counter = 0;

  //threads

  // Set the first setup of the Robot
  if(MAPPING_ENABLED){
    // Get first target mark - 0
    TargetMark = TRACK_EVENT_NAME[currentMark];
    acceleration = TargetMark.acceleration;
    // Update Robot Setup
    setupPID(TargetMark.setup);
  }else {
    // Get first target mark - 0
    TargetMark = TRACK_EVENT_NAME[currentMark];
    acceleration = TargetMark.acceleration;
    // Update Robot Setup
    setupPID(Normal);
  }
}

void setup(){
  delay(1000);
  PC.begin(PC_SPEED);
  BT.begin(BT_SPEED);
  LOG.println(PROJECT_NAME);
  LOG.println(PROJECT_BOARD);
  LOG.println(PROJECT_VERSION);
  setupLeftEncoder();
  setupRightEncoder();
  setupMarkSensors();
  // setupLineReader();
  setupPID(Normal);
  setupRobot();
}


//TEST MOTORS
void testMotor(){

    LOG.println("Test Left in 25%");
    LeftMotor.speed(25);
    delay(1000);
    LOG.println("Test Left in 50%");
    LeftMotor.speed(50);
    delay(1000);
    LOG.println("Test Left in 100%");
    LeftMotor.speed(100);
    delay(1000);
    LOG.println("Coast Left");
    LeftMotor.coast();
    delay(1000);
    LOG.println("Brake Left");
    LeftMotor.brake();
    delay(1000);
    LOG.println("Test reverse Left in -25%");
    LeftMotor.speed(-25);
    delay(1000);
    LOG.println("Test reverse Left in -50%");
    LeftMotor.speed(-50);
    delay(1000);
    LOG.println("Coast Left");
    LeftMotor.coast();
    delay(1000);
    LOG.println("Brake Left");
    LeftMotor.brake();
    delay(1000);

    LOG.println("Test Right in 25%");
    RightMotor.speed(25);
    delay(1000);
    LOG.println("Test Right in 50%");
    RightMotor.speed(50);
    delay(1000);
    LOG.println("Test Right in 100%");
    RightMotor.speed(100);
    delay(1000);
    LOG.println("Coast Right");
    RightMotor.coast();
    delay(1000);
    LOG.println("Brake Right");
    RightMotor.brake();
    delay(1000);
    LOG.println("Test reverse Right in -25%");
    RightMotor.speed(-25);
    delay(1000);
    LOG.println("Test reverse Right in -50%");
    RightMotor.speed(-50);
    delay(1000);
    LOG.println("Coast Right");
    RightMotor.coast();
    delay(1000);
    LOG.println("Brake Right");
    RightMotor.brake();
    delay(3000);

}

//TEST ENCODER
void leftEncoder() {
  LeftEncoder.encode();
}

void setupLeftEncoder() {
  //X2 encoding uses interrupts on only channel A.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC1_A), leftEncoder, CHANGE);

  //X4 encoding uses interrupts on      channel A,
  //and on channel B.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC1_B), leftEncoder, CHANGE);
}

void rightEncoder() {
  RightEncoder.encode();
}

void setupRightEncoder() {
  //X2 encoding uses interrupts on only channel A.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC2_A), rightEncoder, CHANGE);

  //X4 encoding uses interrupts on      channel A,
  //and on channel B.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC2_B), rightEncoder, CHANGE);
}

void testEncoder(bool AUTO_ENCODER){

    LOG.println("Starting Test Encoder");
    delay(500);

    while(!AUTO_ENCODER){
        LOG.print("Left: ");
        LOG.print("\t");
        LOG.print(LeftEncoder.getPulses());
        LOG.print("\t");
        LOG.print("Right: ");
        LOG.print("\t");
        LOG.print(RightEncoder.getPulses());
        LOG.println();
        delay(100);
    }
    while(AUTO_ENCODER){
        LOG.print("Left: ");
        LOG.print("\t");
        LeftMotor.speed(25);
        delay(1000);
        int leftPulses = LeftEncoder.getPulses();
        LOG.print(leftPulses);
        if(leftPulses>0)
            LOG.println("\t Left working");
        else if(leftPulses<0)
            LOG.println("\t Change Channels");
        else
            LOG.println("\t Fail");
        LeftMotor.brake();

        delay(1000);

        LOG.print("Right: ");
        LOG.print("\t");
        RightMotor.speed(25);
        delay(1000);
        int RightPulses = RightEncoder.getPulses();
        LOG.print(RightPulses);
        if(RightPulses>0)
            LOG.println("\t Right working");
        else if(RightPulses<0)
            LOG.println("\t Change Channels");
        else
            LOG.println("\t Fail");
        RightMotor.brake();
    delay(500);
    LOG.println("Done");
    LeftEncoder.reset();
    RightEncoder.reset();
  }
}

//Line Sensor
void setupLineReader() {
  delay(2000);
  LOG.print("Calibrating sensors...");
  digitalWrite(PIN_LED, 1);
  for (int i = 0; i < 1000; i++)
    LineReader.calibrate(true);
  LOG.println("Done.");
  delay(2000);
  digitalWrite(PIN_LED, 0);
  //
  // for (int i = 0; i < NUM_SENSORS; i++)
  //   LOG.printf("Min: %4i \t", LineReader.calibratedMinimumOn[i]);
  //
  // LOG.printf("%s", "\n");
  //
  // for (int i = 0; i < NUM_SENSORS; i++)
  //   LOG.printf("Max: %4i \t", LineReader.calibratedMaximumOn[i]);

  // LOG.printf("%s", "\n");
}

void testLineSensor(){
// Certifies correct operation of line sensors
  LineReader.read(sensorValues, QTR_EMITTERS_ON);
   for (int i = 0; i < NUM_SENSORS; i++) {
    LOG.print(sensorValues[i]);
    LOG.print("\t");
  }
  // Position of the line: (left)-2500 to 2500(right)
  linePosition = LineReader.readLine(sensorValues, QTR_EMITTERS_OFF, WHITE_LINE) - ((NUM_SENSORS-1)*500);
  LOG.println(linePosition);
}

void testPID(){
  LineReader.read(sensorValues, QTR_EMITTERS_ON);
  linePosition = LineReader.readLine(sensorValues, QTR_EMITTERS_OFF, WHITE_LINE) - ((NUM_SENSORS-1)*500);
  directioncontrol.setProcessValue(linePosition);
  directiongain = directioncontrol.compute();
  LOG.print("Gain of PID: \t");
  LOG.println(directiongain);

}

void loop(){
  // testMotor();
  // testEncoder(false);
  // testLineSensor();
  // testPID();
  followLine();
  // delay(100);
}

void followLine(){

  // Timers
  startLogTimer = millis()/1000.0; // Debug the loop
  startLapTimer = millis()/1000.0; // Time of a lap
  startAccTimer = millis()/1000.0; // Acceleration interval
  startCps_left_led_timer = millis()/1000.0; // Acceleration interval
  startCps_right_led_timer = millis()/1000.0; // Acceleration interval

  while(1){
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
    nowLapTimer = millis()/1000.0;
    if (nowLapTimer - startLapTimer > LAP_TIME && STOP_BY_TIME) {
      startLapTimer = nowLapTimer;
      robotstate = false; // Stop the robot
    }

    if (!robotstate) { // Stop the Robot
      // Stop the robot and release the motors after
      LeftMotor.brake();
      RightMotor.brake();
      delay(500);
      LeftMotor.coast();
      RightMotor.coast();

      // Stop the Lap Timer
      startLapTimer = millis()/1000.0;

      // Print some data for statistics
      float laptime = nowLapTimer - startLapTimer;
      float mediumspeed = currentPosition / laptime;
      LOG.print("Time Lap: \t");       LOG.print(laptime);
      LOG.print("\t");
      LOG.print("Track Length: \t ");  LOG.print(currentPosition);
      LOG.print("\t");
      LOG.print("Medium Speed: \t ");  LOG.print(mediumspeed);
      LOG.println();

      // Blink the LEDs
      while (!robotstate) {
        digitalWrite(PIN_LED, !digitalRead(PIN_LED));
        delay(500);
      }
    }
    else if (robotstate) { // Follow the Line

        //LEDS turn off - About Interrupt
        nowCps_left_led_timer = millis()/1000.0;
        if (nowCps_left_led_timer - startCps_left_led_timer > 0.150) {
          digitalWrite(PIN_LED,0);
          startCps_left_led_timer = nowCps_left_led_timer;
        }

        if (nowCps_right_led_timer - startCps_right_led_timer > 0.150) {
          digitalWrite(PIN_LED,0);
          startCps_right_led_timer = nowCps_right_led_timer;
        }


        // Check if changed mark
        if (currentPosition >= TargetMark.position && MAPPING_ENABLED) {
          currentMark++;
          // Get current Target Mark
          TargetMark = TRACK_EVENT_NAME[currentMark];
          acceleration = TargetMark.acceleration;
          // Update Robot Setup
          setupPID(TargetMark.setup);
        }

        // Position of the line: (left)-2500 to 2500(right)
        LineReader.read(sensorValues, QTR_EMITTERS_ON);
        linePosition = LineReader.readLine(sensorValues, QTR_EMITTERS_OFF, WHITE_LINE) - 2500.0;

        directioncontrol.setProcessValue(linePosition);
        directiongain = directioncontrol.compute();

        // Speed update with acceleration
        if (ACCELERATION_ENABLED) {
          nowAccTimer = millis()/1000.0;
          if (nowAccTimer - startAccTimer > ACCELERATION_INTERVAL) {
            // check if the robot accelerates or decelerates
            if ((acceleration > 0 && currentSpeed < targetSpeed) || (acceleration < 0 && currentSpeed > targetSpeed)) {
              currentSpeed += acceleration * ACCELERATION_INTERVAL;
              currentSpeed = currentSpeed > targetSpeed ? targetSpeed : currentSpeed < 0 ? 0 : currentSpeed;
              startAccTimer = nowAccTimer;
            }
          }
        } else {
          currentSpeed = targetSpeed;
        }

        // Set the Direction
        leftmotorspeed = currentSpeed + (directiongain > 0 ? -directiongain : 0);
        righmotorspeed = currentSpeed + (directiongain < 0 ? +directiongain : 0);

        // Constrain the speed value to [0, 100] interval
        leftmotorspeed = leftmotorspeed > 100 ? 100 : leftmotorspeed < -REVERSE ? -REVERSE : leftmotorspeed;
        righmotorspeed = righmotorspeed > 100 ? 100 : righmotorspeed < -REVERSE ? -REVERSE : righmotorspeed;

        // LOG.printf("PID is working? %f \n", directiongain);
        if(MOTORS_ENABLE){
          LeftMotor.speed(leftmotorspeed);
          RightMotor.speed(righmotorspeed);
        }
      }

      nowLogTimer = millis()/1000.0;
      if (nowLogTimer - startLogTimer > LOG_INTERVAL && LOG_ENABLED) {
        // Certifies correct operation of encoders
        // LOG.print(LeftEncoder.getPulses());
        // LOG.print("\t ");
        // LOG.print(RightEncoder.getPulses());
        // LOG.print("\t ");
        // LOG.print(leftDistance);
        // LOG.print("\t ");
        // LOG.print(rightDistance);
        // LOG.print("\t ");
        // LOG.print(currentPosition);
        // LOG.print("\t ");
        // LOG.print(TargetMark.position);
        // LOG.print("\t ");
        // LOG.print(currentMark);
        // LOG.print("\t ");

        // Certifies correct operation of line sensors
        // LineReader.read(sensorvalues, QTR_EMITTERS_ON);
        //  for (int i = 0; i < 6; i++) {
        //   LOG.printf("%i \t", sensorvalues[i]);
        // }
        // LOG.printf("%i \n", linePosition);

        // LOG.printf("Mark: %i \t", MarksensorTest.read());


       // Certifies correct operation of encoders
       // LOG.printf("Left Encoder: %i \t", LeftEncoder.getPulses());
       // LOG.printf("Right Encoder: %i \t", RightEncoder.getPulses());
       // LOG.printf("%.4f\t", leftDistance);
       // LOG.printf("%.4f\t", rightDistance);

       // Certifies correct operation of motors
       // LOG.print("PID is working? \t");
       // LOG.print(directiongain);
       // LOG.print("\t ");
       // LOG.print("\t");
       // LOG.print(leftmotorspeed);
       // LOG.print("\t ");
       // LOG.print("\t");
       // LOG.print(righmotorspeed);
       // LOG.print("\t ");
       // LOG.print(targetSpeed);

        // Manual Track Mapping
        // LOG.printf("%.2f,", LapTimer.read());
        // LOG.printf("%i,", currentMark);
        // LOG.printf("%i", linePosition);

        // LOG.printf("%.4f,", currentPosition);
        // LOG.printf("%.4f", DIF(leftDistance, rightDistance));

        // START
        // Checkpoint sensors mapping
        // Crossroad
        /*
        if (checkpoint_left_counter != last_checkpoint_left_counter && checkpoint_right_counter != last_checkpoint_right_counter) {
          crossroad_counter++;
          LOG.print("C,");
          LOG.print(crossroad_counter);
          LOG.print(",");
          checkpoint_left_counter--;
          checkpoint_right_counter--;
        }
        // Curve start/end marks
        else if (checkpoint_left_counter != last_checkpoint_left_counter && checkpoint_right_counter == last_checkpoint_right_counter) {
          LOG.print("L,");
          LOG.print(checkpoint_left_counter);
          LOG.print(",");
          last_checkpoint_left_counter = checkpoint_left_counter;
        }
        // Start/Finish marks
        else if (checkpoint_left_counter == last_checkpoint_left_counter && checkpoint_right_counter != last_checkpoint_right_counter) {
          LOG.print("R,");
          LOG.print(checkpoint_right_counter);
          LOG.print(",");
          last_checkpoint_right_counter = checkpoint_right_counter;
        }
        else {
          LOG.print("-,-,");
        }
*/
        // Encoders positions
        // LOG.print(",");
        // LOG.print(leftDistance);
        // LOG.print(",");
        // LOG.print(rightDistance);

        // LOG.printf("%i", checkpoint_right_counter);
        //Test of Mapping
        // LOG.printf("CurrentPosition: %.2f \t", currentPosition);
        // LOG.printf("CurrentSpeed: %.2f \t", TargetMark.setup.speed);

        // LOG.print(nowAccTimer - startAccTimer);
        // LOG.print("\t ");
        // LOG.print(nowLapTimer - startLapTimer);
        // LOG.print("\t ");
        // LOG.print(nowLogTimer - startLogTimer);
        // LOG.print("\t ");
        // LOG.print(nowCps_left_led_timer - startCps_left_led_timer);
        // LOG.print("\t ");
        // LOG.print(nowCps_right_led_timer - startCps_right_led_timer);

        LOG.println();

        // testEncoder(true);
        // testLineSensor();
        // testMotor();
        // testPID();
        //END*/
        startLogTimer = nowLogTimer;
      }
    }
  }
