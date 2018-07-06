#ifndef CONFIG_H
#define CONFIG_H
#include "mbed.h"

//
// Project
//
#define PROJECT_NAME            "Sloth Firmware"
#define PROJECT_VERSION         "v2.0"

//
// Serial DEBUG
//
#define LOG_ENABLED false
#define LOG if(LOG_ENABLED) BT
#define PC_SPEED  115200
#define LOG_INTERVAL  0.01 //

//
// Bluetooth Configs (Type here)
//
#define BT_SPEED  115200
#define BTRX  p9
#define BTTX  p10

//
// Line Reader Settings
//
#define WHITE_LINE  true
#define NUM_SENSORS 6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  1  // average 4 analog samples per sensor reading
#define EMITTER_PIN p14  // emitter is controlled by digital pin 2
#define PIN_LR_S0 p15
#define PIN_LR_S1 p16
#define PIN_LR_S2	p17
#define PIN_LR_S3	p18
#define PIN_LR_S4	p19
#define PIN_LR_S5	p20

//
//Lap Sensor Settings
//
#define CROSS_COUNTER 6
#define PIN_TRACK_MARKING_RIGHT p11
#define PIN_TRACK_MARKING_LEFT  p12

//
// General Settings
//
#define STOP_BY_TIME false
#define LAP_TIME 20 //in seconds
#define STOP_BY_DISTANCE true
#define FINAL_TARGET_POSITION   23.5  // in meters
// #define FINAL_TARGET_POSITION   1.5
#define ACCELERATION_ENABLED true
#define ACCELERATION_INTERVAL 0.01
#define MAPPING_ENABLED true
#define FIRST_MARK_POSITION 0.5

//
//Marking Settings
//

//
// Motors config (H-Bridge)
//
#define REVERSE	0.00
#define PIN_M2_EN   p21
#define PIN_M2_IN1  p22
#define PIN_M2_IN2  p23
#define PIN_M1_EN   p26
#define PIN_M1_IN1  p24
#define PIN_M1_IN2  p25

//
// Encoder config (Quadrature)
//
#define PULSES_PER_REV 179.0 // 30:1
// #define PULSES_PER_REV 61.0 // 10:1
#define PIN_ENC1_A  p27
#define PIN_ENC1_B	p28
#define PIN_ENC2_A	p30
#define PIN_ENC2_B	p29
//#define M_PI 3.14159
#define WHEEL_RADIUS 0.016	// D = 32mm
#define WHEEL_PERIMETER	(2.0*WHEEL_RADIUS*M_PI)	// WHEEL_RADIUS * PI
#define PULSES2DISTANCE(p) (p / PULSES_PER_REV * WHEEL_PERIMETER)
#define AVG(l,r) ((l + r) / 2.0)
#define DIF(l,r) (r - l)
//
// Pulses to Distance
//

#define SlowCurve 0
#define Curve     1
#define FastCurve 2
#define Straight  3
#define Stop      4

#define TRACK_EVENT_NAME HACKPULICA_V2
#define GAIN_NUMBER k3

#endif
