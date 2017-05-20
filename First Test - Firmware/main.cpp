#include "mbed.h"
#include "_config.h"

// Average of both motors
   PwmOut pwmM1(PIN_M1_EN);
   PwmOut pwmM2(PIN_M2_EN);
   
   DigitalOut in1M1(PIN_M1_IN1);
   DigitalOut in2M1(PIN_M1_IN2);
   DigitalOut in1M2(PIN_M2_IN1);
   DigitalOut in2M2(PIN_M2_IN2);
	
// Line Reader
	AnalogIn inSensors[6] = {
		PIN_LR_S0,
		PIN_LR_S1,
		PIN_LR_S2,
		PIN_LR_S3,
		PIN_LR_S4,
		PIN_LR_S5
	};
	
//	AnalogIn inLR_S0(PIN_LR_S0);
//	AnalogIn inLR_S1(PIN_LR_S1);
//	AnalogIn inLR_S2(PIN_LR_S2);
//	AnalogIn inLR_S3(PIN_LR_S3);
//	AnalogIn inLR_S4(PIN_LR_S4);
//	AnalogIn inLR_S5(PIN_LR_S5);
	
	DigitalIn inMarkingL(PIN_LR_S0);
	DigitalIn inMarkingR(PIN_LR_S0);

//Serial

	Serial logOut(USBTX, USBRX); // tx, rx
	
	
	float values[6];
	int SENSOR_MIN = 10;
	int SENSOR_MAX = 100;

	static unsigned long start;
  static unsigned long lastStart;
  static unsigned long startedTime;
  
  static bool started;
  static int8_t lastSide;
  static double integral;
  static double realError;
  static float lastError;
  unsigned long last_time = 0;
  static float steer;
  unsigned int side;
	
	float derivative;
  float curve;
  float speedDown;
  float m1;
  float m2;
  int dt = 0;
	
	
///PID

	float desired;     //< set point

	float prevError;    //< previous error
	float integ;        //< integral

	float kp;           //< proportional gain
	float ki;           //< integral gain
	float kd;           //< derivative gain

	float iLimit;       //< integral limit

		#define	BASE_SPEED						0
		#define K_INTEGRAL            0.0000000
    #define K_DERIVATIVE          150 
    #define K_PROPORTINAL         0
		#define K_LIMIT								0
		#define OBJECTIVE							0

void readValues(int nSensors){
		for (int i = 0; i < nSensors; i++)
				values[i] = inSensors[i].read();
	
//	values[0] = inLR_S0.read();		
//	values[1] = inLR_S1.read();		
//	values[2] = inLR_S2.read();		
//	values[3] = inLR_S3.read();		
//	values[4] = inLR_S4.read();		
//	values[5] = inLR_S5.read();		
}

int getValue(int index){
	return values[index];
}

float getPosition(){
	float weighted_sum = 0;
  float sum = 0;
  for(int i = 0; i < 6; i++){
    float value = -(float)getValue(i) / (SENSOR_MAX - SENSOR_MIN) + 1.0;
    weighted_sum = weighted_sum + value  * (i + 1);
    sum = sum + value;
  }
  // Serial.println();
  float position = -((weighted_sum / sum));
  return position;
}

///////////////MOTORS////////////////////////

//// Set power of both DC motors
void Motors_setPower(float m1, float m2){

    // Limit Powers
    //m1 = min(max(m1, -100.0), 100.0);
    //m2 = min(max(m2, -100.0), 100.0);

    // Map powers
    float powerOutA = m1 / 100.0;
    float powerOutB = m2 / 100.0;

    // Set power
    pwmM1.write(powerOutA);
    pwmM2.write(powerOutB);

    // Set Directions
    in1M1 = powerOutA >  0 ? 1 : 0;
    in2M1 = powerOutA >= 0 ? 0 : 1;

    in1M2 = powerOutB >  0 ? 1 : 0;
    in2M2 = powerOutB >= 0 ? 0 : 1;
}

void Motors_stop(){
    // Stop motor 1
    pwmM1.write(0);
    in1M1 = 0;
    in2M1 = 0;

    // Stop motor 2
    pwmM2.write(0);
    in1M2 = 0;
    in2M2 = 0;
}

//// Initialize pins
void Motors_init(){
    pwmM1.period(PWM_PERIOD);
    pwmM2.period(PWM_PERIOD);
    Motors_setPower(0, 0);
}

void PID(float _kp, float _ki, float _kd, float _iLimit = 100){
    kp = _kp;
    ki = _ki;
    kd = _kd;
    iLimit = _iLimit;
    integ = 0;
    prevError = 0;
}

void PID_setSetPoint(float target){
    desired = target;
}

float PID_update(float input, float dt){
    float error = desired - input;

    integ = integ + error * dt * ki;

    if (integ > iLimit){
        integ = iLimit;
    }else if (integ < -iLimit){
        integ = -iLimit;
    }

    float deriv = (error - prevError) / dt;

    float output = kp * error + kd * deriv + integ;

    prevError = error;

    return output;
}

//void PID_clear(){
//    prevError = integ = 0;
//}


int main() {
    
		Motors_init();
		PID(K_PROPORTINAL,K_INTEGRAL,K_DERIVATIVE,K_LIMIT);
		PID_setSetPoint(OBJECTIVE);
		float outPID;
		float position;
	while(1) {
		readValues(6);
		position = getPosition();
		logOut.printf("%d: %.10f \t", 0, getPosition());
		logOut.printf("\n");
		wait(.25);
		
		outPID = PID_update(position,1);
		
		Motors_setPower(BASE_SPEED + 	outPID,BASE_SPEED - 	outPID );
		
	}
}

