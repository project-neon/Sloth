
#include "Motor.h"
// #include "Encoder.h"
#include "_config.h"
#include "QEI.h"
#include "QTRSensors.h"

Motor LeftMotor(PIN_M1_PWM, PIN_M1_IN1, PIN_M1_IN2);
Motor RightMotor(PIN_M2_PWM, PIN_M2_IN1, PIN_M2_IN2);

QEI LeftEncoder(PIN_ENC1_A, PIN_ENC1_B, PULSES_PER_REV, WHEEL_RADIUS);
QEI RightEncoder(PIN_ENC2_A, PIN_ENC2_B, PULSES_PER_REV, WHEEL_RADIUS);

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

int linePosition;
// Function to calibrate the line reader
void lineReaderCalibrate() {

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



void setup(){
  PC.begin(PC_SPEED);
  BT.begin(BT_SPEED);
  LOG.println("Starting Test Motor");
  setupLeftEncoder();
  setupRightEncoder();
  lineReaderCalibrate();
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

void testLineSensor(){
// Certifies correct operation of line sensors
  LineReader.read(sensorValues, QTR_EMITTERS_ON);
   for (int i = 0; i < NUM_SENSORS; i++) {
    LOG.print(sensorValues[i]);
    LOG.print("\t");
  }
  // Position of the line: (left)-2500 to 2500(right)
  linePosition = LineReader.readLine(sensorValues, QTR_EMITTERS_OFF, WHITE_LINE)- ((NUM_SENSORS-1)*500);
  LOG.println(linePosition);


}
void loop(){
  // delay(2000);
  // testMotor();
  // testEncoder(True);
  testLineSensor();
  delay(100);
}
