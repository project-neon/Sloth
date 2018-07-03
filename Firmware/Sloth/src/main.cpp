// #include "Motor.h"
// #include "QTRSensors.h"
// #include "PID.h"
// #include "QEI.h"
// #include "_config.h"
// #include "tracks.h"
// #include "LineReader.h"
// #include "DistanceReader.h"
// #include "CheckpointReader.h"
//
// // #include "settingsSpeed.h"
//
// // Timers
// Timer LogTimer; // Debug the loop
// Timer LapTimer; // Time of a lap
// Timer AccTimer; // Acceleration interval
//
// // Robot status variables
// // position reference by the travelled distance in meters
// float travelled_distance;
// // position of the sensor on the line[-1,1]
// float line_position;
// // position reference by the checkpoint marks in the track
// int current_checkpoint;
// // current target speed
// float target_speed;
//
// // Serial
// //Control the Communication with a Computer (Serial) and HC-05
// Serial PC(USBTX, USBRX);
// Serial BT(BTRX, BTTX);
//
// // Leds
// DigitalOut leds[4] = {
//     LED1,
//     LED2,
//     LED3,
//     LED4
// };
//
// // Motors
// Motor LeftMotor(PIN_M1_EN, PIN_M1_IN1, PIN_M1_IN2); // Lefut Motor
// Motor RightMotor(PIN_M2_EN, PIN_M2_IN1, PIN_M2_IN2); // Right Motor
// float leftmotorspeed = 0.0;
// float righmotorspeed = 0.0;
// float currentSpeed = 0.0;
// float targetSpeed = 0.0;
// float acceleration = 0.0;
//
// bool robotstate = true;
// bool readyStatus = true;
//
// //PID
// float directiongain = 0.0;
// PID directioncontrol(0, 0, 0);
//
// float speedbase = 0.6;
// float kpdir = 0.00022;
// float kidir = 0.000000;
// float kddir = 0.0000050;
//
// Setup Normal = {speedbase, kpdir, kidir, kddir};
//
// void setRobotSetup(Setup setup) {
//   // Setup PID and Speed
//   targetSpeed = setup.speed;
//   directioncontrol.setTunings(setup.kp, setup.ki, setup.kd);
//   // If line position is 0, the robot is just over the line
//   directioncontrol.setSetPoint(0);
// }
//
// // The target mark
// Mark TargetMark;
// int currentMark = 0;
// float POSITION_FIX =0;
//
// void btcallback() {
//   char rcvd = BT.getc();
//   switch (rcvd) {
//     case 'A':
//       kpdir += 0.01;
//       break;
//     case 'B':
//       kpdir -= 0.01;
//       break;
//     case 'C':
//       kidir += 0.0000001;
//       break;
//     case 'D':
//       kidir -= 0.0000001;
//       break;
//     case 'E':
//       kddir += 0.000001;
//       break;
//     case 'F':
//       kddir -= 0.000001;
//       break;
//     case 'G':
//       speedbase += 0.01;
//       break;
//     case 'H':
//       speedbase -= 0.01;
//       break;
//     case 'I':
//       robotstate = false;
//       break;
//     case 'J':
//       LOG.printf("Encoder Right Now: %.0f \n", travelled_distance);
//       break;
//     case 'K':
//       readyStatus = true;
//       // robotstate = true;
//       LOG.printf("Robot will Start in 2s");
//       wait(2);
//       break;
//     case 'L':
//       readyStatus = false;
//       // robotstate = true;
//       LOG.printf("Robot Paused");
//       break;
//   }
//    directioncontrol.setTunings(kpdir, kidir, kddir);
//    // BT.printf("%.8f %.8f %.2f\n", kpdir, kddir, speedbase);
// }
//
// int main() {
//
//   CheckpointReader::init();
//
//   // Setup Serial and Welcome message
//   PC.baud(PC_SPEED);
//   BT.baud(BT_SPEED);
//   BT.attach(&btcallback);
//   LOG.printf("%s ", PROJECT_NAME); LOG.printf("%s\n", PROJECT_VERSION);
//
//
//   // Release motors for make more easy the calibration
//   LeftMotor.coast();
//   RightMotor.coast();
//
//   // Calibrate the line sensor
//   wait(2);
//   LOG.printf("%s", "Calibrating the Line Sensors... ");
//   LineReader::calibrate(500);
//   LOG.printf("%s\n", "done!");
//   wait(4);
//
//   // Reset Encoders
//   DistanceReader::reset();
//
//   // Clear mark sensors counters
//   ms1count = 0;
//   ms2count = 0;
//
//   // Start Timers
//   LogTimer.start();
//   LapTimer.start();
//   AccTimer.start();
//
//   // Set the first setup of the Robot
//   if(MAPPING_ENABLED){
//     // Get first target mark - 0
//     TargetMark = TRACK_EVENT_NAME[currentMark];
//     acceleration = TargetMark.acceleration;
//     // Update Robot Setup
//     setRobotSetup(TargetMark.setup);
//   } else {
//     // Get first target mark - 0
//     TargetMark = TRACK_EVENT_NAME[currentMark];
//     acceleration = TargetMark.acceleration;
//     // Update Robot Setup
//     setRobotSetup(Normal);
//   }
//   // Main Loop
//   while(1) {
//
//     // Get the currrent travelled distance in meters
//     float travelled_distance = DistanceReader::getDistance();
//
//     // Check if the robot complete the track
//     if (travelled_distance >= FINAL_TARGET_POSITION && STOP_BY_DISTANCE) {
//       robotstate = false; // Stop the Robot
//     }
//
//     // Checks if medium lap time has been reached
//     if (LapTimer.read() > LAP_TIME && STOP_BY_TIME) {
//       LapTimer.stop();
//       robotstate = false; // Stop the robot
//     }
//
//     if (currentMark>0)
//       Marksensor1.disable_irq();
//
//     if (!robotstate) { // Stop the Robot
//       // Stop the robot and release the motors after
//       LeftMotor.brake();
//       RightMotor.brake();
//       wait(.500);
//       LeftMotor.coast();
//       RightMotor.coast();
//
//       // Stop the Lap Timer
//       LapTimer.stop();
//
//       // Print some data for statistics
//       float laptime = LapTimer.read();
//       float mediumspeed = travelled_distance / laptime;
//       LOG.printf("Time Lap: %.5f\t", laptime);
//       LOG.printf("Track Length: %.2fm\t ", travelled_distance);
//       LOG.printf("Medium Speed: %.2fm/s\t ",  mediumspeed);
//       LOG.printf("%s\n", "");
//
//       // Blink the LEDs
//       while (1) {
//         for (int i = 0; i <= 3; i++) {
//           for (int j = 0; j <= 3; j++) {
//             leds[j] = j == i;
//             wait(.050);
//           }
//         }
//       }
//     }
//
//     else if (robotstate && readyStatus) { // Follow the Line
//
//       //LEDS turn off - About Interrupt
//       leds[2]=0;
//       leds[3]=0;
//
//       // Check if changed mark
//       if (travelled_distance >= TargetMark.position && MAPPING_ENABLED) {
//         currentMark++;
//         // Get current Target Mark
//         TargetMark = TRACK_EVENT_NAME[currentMark];
//         acceleration = TargetMark.acceleration;
//         // Update Robot Setup
//         setRobotSetup(TargetMark.setup);
//       }
//
//       // Position of the line: (left)-1.0 to 1.0(right)
//       line_position = LineReader::getPosition();
//
//       directioncontrol.setProcessValue(line_position);
//       directiongain = directioncontrol.compute();
//
//       // Speed update with acceleration
//       if (ACCELERATION_ENABLED) {
//         if (AccTimer.read() > ACCELERATION_INTERVAL) {
//           // check if the robot accelerates or decelerates
//           if ((acceleration > 0 && currentSpeed < targetSpeed) || (acceleration < 0 && currentSpeed > targetSpeed)) {
//             currentSpeed += acceleration * ACCELERATION_INTERVAL;
//             currentSpeed = currentSpeed > targetSpeed ? targetSpeed : currentSpeed < 0.0 ? 0.0 : currentSpeed;
//             AccTimer.reset();
//           }
//         }
//       } else {
//         currentSpeed = targetSpeed;
//       }
//
//       // Set the Direction
//       leftmotorspeed = currentSpeed + (directiongain > 0 ? -directiongain : 0);
//       righmotorspeed = currentSpeed + (directiongain < 0 ? +directiongain : 0);
//
//       // Constrain the speed value to [0.0, 1.0] interval
//       leftmotorspeed = leftmotorspeed > 1.0 ? 1.0 : leftmotorspeed < -REVERSE ? -REVERSE : leftmotorspeed;
//       righmotorspeed = righmotorspeed > 1.0 ? 1.0 : righmotorspeed < -REVERSE ? -REVERSE : righmotorspeed;
//
//       // LOG.printf("PID is working? %f \n", directiongain);
//       // LeftMotor.speed(leftmotorspeed);
//       // RightMotor.speed(righmotorspeed);
//
//     // Test Motors
//       // LeftMotor.speed(0.5);
//       // RightMotor.speed(0.5);
//       // wait(2);
//       // LeftMotor.brake();
//       // RightMotor.brake();
//       // wait(2);
//       // LeftMotor.speed(-0.5);
//       // RightMotor.speed(-0.5);
//       // wait(2);
//       // LeftMotor.brake();
//       // RightMotor.brake();
//       // wait(2);
//     }
//
//     if (LogTimer.read() > LOG_INTERVAL && LOG_ENABLED) {
//       // LOG.printf("%i\t", travelled_distance);
//       // LOG.printf("%i\t", TargetMark.position);
//       // LOG.printf("%i\t", currentMark);
//
//       // Certifies correct operation of line sensors
//       // LineReader.read(sensorvalues, QTR_EMITTERS_ON);
//        for (int i = 0; i < 6; i++)
//         LOG.printf("%i \t", LineReader::getValue(i));
//
//       LOG.printf("Line: %f \t", line_position);
//
//       // LOG.printf("Mark: %i \t", MarksensorTest.read());
//
//
//      // Certifies correct operation of encoders
//      // LOG.printf("Left Encoder: %i \t", LeftEncoder.getPulses());
//      // LOG.printf("Right Encoder: %i \t", RightEncoder.getPulses());
//      // LOG.printf("%.4f\t", leftDistance);
//      // LOG.printf("%.4f\t", rightDistance);
//
//      // Certifies correct operation of motors
//      // LOG.printf("PID is working? %f \n", directiongain);
//      // LOG.printf("%.2f\t", leftmotorspeed);
//      // LOG.printf("%.2f\t", righmotorspeed);
//
//       // Manual Track Mapping
//       // LOG.printf("%.2f ", LapTimer.read());
//       // LOG.printf("Line: %i \t", line_position);
//       // LOG.printf("%.4f,", travelled_distance);
//       // LOG.printf("%.4f", DIF(leftDistance, rightDistance));
//
//       //Test of Mapping
//       // LOG.printf("CurrentPosition: %.2f \t", travelled_distance);
//       // LOG.printf("CurrentMark: %i \t", currentMark);
//       // LOG.printf("CurrentSpeed: %.2f \t", TargetMark.setup.speed);
//
//
//       LOG.printf("%s\n","");
//       LogTimer.reset();
//     }
//   }
//
// }
