#include <Arduino.h>
#include "config.h"
#include "TB6612FNG.h"
//#include "QEI.h"


// Encoders
QEI LeftEncoder (PIN_ENC1_A, PIN_ENC1_B, NULL, PULSES_PER_REV); // Left Encoder
QEI RightEncoder (PIN_ENC2_A, PIN_ENC2_B, NULL, PULSES_PER_REV); // Right Encoder

void setup() {
  Serial.begin(115200);
  setupEnc1();
  setupEnc2();
}

void loop() {
  Serial.print(LeftEncoder.getPulses());
  Serial.print("\t");
  Serial.print(RightEncoder.getPulses());
  Serial.print("|\t");
  Serial.print(LeftEncoder.getRevolutions());
  Serial.print("\t");
  Serial.print(RightEncoder.getRevolutions());
  Serial.print("\n");
  delay(1000);
}


void enc1() {
  LeftEncoder.encode();
}

void setupEnc1() {
  //X2 encoding uses interrupts on only channel A.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC1_A), enc1, CHANGE);

  //X4 encoding uses interrupts on      channel A,
  //and on channel B.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC1_B), enc1, CHANGE);
}

void enc2() {
  RightEncoder.encode();
}

void setupEnc2() {
  //X2 encoding uses interrupts on only channel A.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC2_A), enc2, CHANGE);

  //X4 encoding uses interrupts on      channel A,
  //and on channel B.
  attachInterrupt(digitalPinToInterrupt(PIN_ENC2_B), enc2, CHANGE);
}
