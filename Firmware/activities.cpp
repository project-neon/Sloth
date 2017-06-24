
#include "_config.h"
#include "mbed.h"

bool lineDetectedRight = false;
bool lineDetectedLeft = false;

void lapSensorActivated(){
  lineDetectedRight = true;
}

// ====================================
// ACTIVITY: Line Follower
// ====================================

#define TIME_INTERVAL     600
#define TIME_TO_START     TIME_INTERVAL * 3

//int SECCONDS = 23;

lapRight.rise(&lapSensorActivated);

// ====================================
// ACTIVITY: Test Motors
// ====================================
void activityActuators_run(){
  if(Runner::invalidated){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 5);
    display.print("Test Actuators");
  }

  if(Bluetooth::read() == "STOP"){
    Motors::setPower(0, 0);
    return;
  }

  int btState = Interface::read();

  if(btState == "IDDLE"){
    Motors::setPower(0, 0);
    Bluetooth::Send(" ( ) ");
  }else if(btState == "BACK"){
    Motors::setPower(-100, -100);
    Bluetooth::Send("V");
  }else if(btState == "UP"){
    Motors::setPower(100, 100);
    Bluetooth::Send("^");
  }
}

// ====================================
// ACTIVITY: Line Follower
// ====================================
float error = 0;
void activityLineFollower_run(){
  static unsigned long start;
  static unsigned long lastStart;
  static unsigned long startedTime;

  static bool started;
  static double lastSide;
  static double integral;
  static double realError;
  static float lastError;

  if(Runner::invalidated){
    lastSide = 0;
//     start = millis();
//     started = false;
//     integral = 0;
//     realError = 0;
//     lastError = 0;
//
//     display.clearDisplay();
//     display.setTextSize(1);
//     display.setTextColor(BLACK, WHITE);
//     display.setCursor(20, 5);
//     display.print("Line Follow");
//     display.display();
//     Runner::invalidated = false;
//
//     Robot::doBeep(3, TIME_INTERVAL);
//   };
//   int btn = Interface::readBtnState();
//   if(!started){
//     display.setTextSize(3);
//     display.setTextColor(WHITE, BLACK);
//     display.setCursor(45, 30);
//     if(btn == STICK_CENTER){
//       display.print("GO!");
//
//       // Set started flag
//       started = true;
//       startedTime = millis();
//     }else{
//       if(btn == STICK_DOWN)
//         SECCONDS--;
//       else if(btn == STICK_UP)
//         SECCONDS++;
//
//       display.print(SECCONDS);
//     }
//     display.display();
//     return;
//   }
//
//
//   //Lap Sensor Interrupt
//
//   float g[3];
//   float derivative;
//   float curve;
//   float speedDown;
//   float m1;
//   float m2;
//   int dt = 0;
//   lastStart = micros();
//   //unsigned long start;
//   while(true){
//     start = micros();
//     dt = start - lastStart;
//     lastStart = start;
//
//     if(Interface::readBtnState() == STICK_LEFT){
//       Motors::setPower(0, 0);
//       Motors::setSteering(0, true);
//       Runner::exit();
//       detachInterrupt(digitalPinToInterrupt(1));
//       return;
//     }
//
//     //
//     // Follow Line controll
//     //
//     #define MINIMUM_SPEED         15
//     #define BASE_SPEED            40
//     #define CURVE_DIFERENTIAL     100
//     #define ERROR_APPROACH        0.4
//
//     #define K_INTEGRAL            0.0000000
//     #define K_DERIVATIVE          0.3875
//     #define K_PROPORTINAL         80.0  //ADD BY VITOR
//
//     // Definições para Steering
//     #define STEERING_NORMAL_MULT  12
//     #define STEERING_CURVE_MULT   60
//     #define STEERING_CURVE_START  0.45
//     #define SPEEDOWN_MULT         0.9
//
//     if(millis() - startedTime > SECCONDS * 1000){//lineDetected){
//       // cross_counter % 2 == 0 ? (PORTE |=  (1<<2)) : (PORTE &= ~(1<<2));
//       lineDetected = false;
//       cross_counter--;
//       // if(cross_counter <= 0){
//         Motors::setPower(0, 0);
//         Motors::setSteering(0, true);
//         Runner::exit();
//         detachInterrupt(digitalPinToInterrupt(1));
//         return;
//       // }
//     }
//
//     //g[0] = K_PROPORTINAL + K_INTEGRAL/2 + K_DERIVATIVE;
//     //g[1] = -K_PROPORTINAL + K_INTEGRAL/2 - 2*K_DERIVATIVE;
//     //g[2] = K_DERIVATIVE;
//
//     //error2 = error1;
//     //error1 = error;
//
//     LineReader::readValues();
//     error = LineReader::getPosition();
//     if(isnan(error)){
//       error = lastSide * 2;
//     }else{
//       lastSide = (error > 0 ? 1 : (error < 0 ? -1 : 0));
//     }
//
//     // Moving average of error
//     realError = realError + (error - realError) * ERROR_APPROACH;
//     // error = realError;
//
//     // Integral
//     integral += dt * min(max(error, -STEERING_CURVE_START), STEERING_CURVE_START) * K_INTEGRAL;
//
//     // Derivative
//     derivative = (error - lastError) * K_DERIVATIVE;
//     lastError = error;
//
//     curve = 0;
//     if(error > STEERING_CURVE_START)
//       curve = error - STEERING_CURVE_START;
//     else if(error < -STEERING_CURVE_START)
//       curve = error + STEERING_CURVE_START;
//
//     // if(Serial){
//     //   Serial.print(error);
//     //   Serial.print(" ");
//     //   Serial.println(curve);
//     // }
//
//     //curve = fabs(error) > STEERING_CURVE_START ?
//     //(error - (fabs(error) / error) * STEERING_CURVE_START) : 0;
//
//     speedDown = 1 - fmax(fmin(fabs(error) - STEERING_CURVE_START, 1.0), 0.0) * SPEEDOWN_MULT;
//     speedDown = speedDown < 0 ? 0 : speedDown;
//
//     m1 = BASE_SPEED + curve * CURVE_DIFERENTIAL; //+ integral - derivative;
//     m2 = BASE_SPEED - curve * CURVE_DIFERENTIAL; // - integral + derivative;
//
//     Motors::setPower(
//       m1 * speedDown,
//       m2 * speedDown
//     );
//
//     Motors::setSteering(error * STEERING_NORMAL_MULT + curve * STEERING_CURVE_MULT);
//     //mv[1] = mv[0];
//     //mv[0] = mv[1] + error*g[0] + error1*g[1] + error2*g[2];
//     //Motors::setSteering(mv[0]);
//     //Serial.println(dt);
//   }
// }
