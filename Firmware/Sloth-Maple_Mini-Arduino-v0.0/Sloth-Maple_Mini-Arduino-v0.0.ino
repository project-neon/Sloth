#include <Arduino.h>
#include "config.h"
#include "TB6612FNG.h"

TB6612FNG MotorDriver1(PIN_M1_PWM, PIN_M1_IN1, PIN_M1_IN2);
TB6612FNG MotorDriver2(PIN_M2_PWM, PIN_M2_IN1, PIN_M2_IN2);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Hello!");
  delay(1000);
  // MotorDriver1.pwm(0.75);
  // MotorDriver2.pwm(0.75);
  // delay(2000);
  // MotorDriver1.brake();
  // MotorDriver2.brake();
  // delay(2000);
  // MotorDriver1.pwm(-0.50);
  // MotorDriver2.pwm(-0.50);
  // delay(2000);
  // MotorDriver1.coast();
  // MotorDriver2.coast();
  // delay(2000);
}
