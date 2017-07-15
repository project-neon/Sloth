#ifndef CONFIG_H
#define CONFIG_H
#include "mbed.h"

//
// Project
//
#define PROJECT_NAME            "Sloth Firmware"
#define PROJECT_VERSION         "v1.0"


//
// Serial DEBUG
//
#define LOG	PC
#define PC_SPEED	115200


//
// Bluetooth Configs (Type here)
//
#define BT_SPEED	9600
#define BTRX	p9
#define BTTX	p10

//
// Line Reader Settings
//
#define WHITE_LINE	1
#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  1  // average 4 analog samples per sensor reading
#define EMITTER_PIN	p14  // emitter is controlled by digital pin 2
#define PIN_LR_S0	p15
#define PIN_LR_S1	p16
#define PIN_LR_S2	p17
#define PIN_LR_S3	p18
#define PIN_LR_S4	p19
#define PIN_LR_S5	p20

//
//Lap Sensor Settings
//
#define CROSS_COUNTER           8
#define PIN_TRACK_MARKING_RIGHT	p13
#define PIN_TRACK_MARKING_LEFT	p12
#define NUMBER_PULSES           29000


//
// Motors config (H-Bridge)
//
//#define SPEED_BASE	0.5
#define PIN_M2_EN               p26
#define PIN_M2_IN1              p24
#define PIN_M2_IN2              p25
#define PIN_M1_EN               p21
#define PIN_M1_IN1              p23
#define PIN_M1_IN2              p22

//
// Encoder config (Quadrature)
//
#define PULSES_PER_REV 180
#define PIN_ENC1_A	p28
#define PIN_ENC1_B	p27
#define PIN_ENC2_A	p30
#define PIN_ENC2_B	p29
#define WHEEL_RADIUS	37	//mm
#define WHEEL_PERIMETER	0.1162389f	// WHEEL_RADIUS * PI = 0.11623892818282234982311780518134


#endif
