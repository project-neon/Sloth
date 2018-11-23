#include "_config.h"
int count = 0;

HardwareTimer timer(1);

#define setPower(pin, power) pwmWrite(pin, map(power, 0, 100, 0, 761)); 

int LS_PINS[] = {
  PIN_LR_S1, 
  PIN_LR_S2, 
  PIN_LR_S3, 
  PIN_LR_S4, 
  PIN_LR_S5, 
  PIN_LR_S6, 
  PIN_LR_S7, 
  PIN_LR_S8
  };

long count1 = 0;
long count2 = 0;

void enc1A(){
  if (digitalRead(PIN_ENC1_B)== HIGH) {
    count1++;
  }else{
    count1--;
  }
}

void enc1B(){
  if (digitalRead(PIN_ENC1_A)== HIGH) {
    count1--;
  }else{
    count1++;
  }
}


void enc2A(){
  if (digitalRead(PIN_ENC2_B)== HIGH) {
    count2--;
  }else{
    count2++;
  }
}

void enc2B(){
  if (digitalRead(PIN_ENC2_A)== HIGH) {
    count2++;
  }else{
    count2--;
  }
}

void setup() {

  // Setup the PWM frequency to ~95kHz (Timer One)
  timer.setPrescaleFactor(1);
  timer.setOverflow(760);
  
  // Start the LOG and print a welcome message
  LOG.begin(115200);
  LOG.println(PROJECT_NAME);
  LOG.println(PROJECT_BOARD);
  LOG.println(PROJECT_VERSION);

  // Define the line sensors pins as input
  for (int pin = 0; pin < NUM_SENSORS; pin++){
    pinMode(LS_PINS[pin], INPUT);
  }

  pinMode(PIN_M1_PWM, PWM);
  pinMode(PIN_M1_IN1, OUTPUT);
  pinMode(PIN_M1_IN2, OUTPUT);
  pinMode(PIN_M2_PWM, PWM);
  pinMode(PIN_M2_IN1, OUTPUT);
  pinMode(PIN_M2_IN2, OUTPUT);

  setPower(PIN_M1_PWM, 0);
  digitalWrite(PIN_M1_IN1, LOW);
  digitalWrite(PIN_M1_IN2, LOW);
  
  setPower(PIN_M2_PWM, 0);
  digitalWrite(PIN_M2_IN1, LOW);
  digitalWrite(PIN_M2_IN2, LOW);

  pinMode(PIN_LED, OUTPUT);

  attachInterrupt(PIN_ENC1_A, enc1A, RISING);
  attachInterrupt(PIN_ENC1_B, enc1B, RISING);
  attachInterrupt(PIN_ENC2_A, enc2A, RISING);
  attachInterrupt(PIN_ENC2_B, enc2B, RISING);
  
  delay(2500);
}

void loop() {

  // Reads the line sensors pins
  for (int pin = 0; pin < NUM_SENSORS; pin++){
    LOG.print(analogRead(LS_PINS[pin]));
    delay(1);
    LOG.print("\t");
  }

  // Print the 
  long reading = analogRead(PIN_BAT_SENSE);
  LOG.print(VBAT_VOLTAGE(reading));
  LOG.print("\t");

  // Print the motor step counter
  LOG.print(count);
  LOG.print("\t");

  // Print the encoders counters
  LOG.print(count1);
  LOG.print("\t");
  LOG.print(count2);
  LOG.print("\t");
  
  switch (count){
    case 0:
      setPower(PIN_M1_PWM, 50);
      setPower(PIN_M2_PWM, 50);
      // Set motor to BACKWARD
      digitalWrite(PIN_M1_IN1, LOW);
      digitalWrite(PIN_M1_IN2, HIGH);
      digitalWrite(PIN_M2_IN1, LOW);
      digitalWrite(PIN_M2_IN2, HIGH);
      count++;
      break;
      
    case 1:
      setPower(PIN_M1_PWM, 0);
      setPower(PIN_M2_PWM, 0);
      digitalWrite(PIN_M1_IN1, HIGH);
      digitalWrite(PIN_M1_IN2, HIGH);
      digitalWrite(PIN_M2_IN1, HIGH);
      digitalWrite(PIN_M2_IN2, HIGH);
      count++;
      break;

    case 2:
      setPower(PIN_M1_PWM, 25);
      setPower(PIN_M2_PWM, 25);
      // Set motor to FORWARD
      digitalWrite(PIN_M1_IN1, HIGH);
      digitalWrite(PIN_M1_IN2, LOW);
      digitalWrite(PIN_M2_IN1, HIGH);
      digitalWrite(PIN_M2_IN2, LOW);
      count++;
      break;

    case 3:
      setPower(PIN_M1_PWM, 0);
      setPower(PIN_M2_PWM, 0);
      digitalWrite(PIN_M1_IN1, HIGH);
      digitalWrite(PIN_M1_IN2, HIGH);
      digitalWrite(PIN_M2_IN1, HIGH);
      digitalWrite(PIN_M2_IN2, HIGH);
      count=0;
      break;
  }

  LOG.print("\n");
  // HEARTBEAT LED
  digitalWrite(PIN_LED, !digitalRead(PIN_LED));
  delay(2500);

}
