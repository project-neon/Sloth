#ifndef CONFIG_H
#define CONFIG_H
#include "mbed.h"

//
// Project
//
#define PROJECT_NAME            "Neo Follower Firmware"
#define PROJECT_VERSION         "v0.4"


//
// Serial DEBUG
//
#define SERIAL_SPEED            115200
#define LOG                     Serial.print


//
// Line Reader Settings
//
#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  1  // average 4 analog samples per sensor reading
#define EMITTER_PIN	p14  // emitter is controlled by digital pin 2
#define PIN_LR_S0	p15
#define PIN_LR_S1	p16
#define PIN_LR_S2	p17
#define PIN_LR_S3	p18
#define PIN_LR_S4	p19
#define PIN_LR_S5	p20
#define PIN_TRACK_MARKING_RIGHT	p12							
#define PIN_TRACK_MARKING_LEFT	p13


//
// Motors config (H-Bridge)
//
#define PIN_M1_EN               p26
#define PIN_M1_IN1              p25
#define PIN_M1_IN2              p24
#define PIN_M2_EN               p21
#define PIN_M2_IN1              p22
#define PIN_M2_IN2              p23

//
// Encoder config (Quadrature)
//
#define PULSES_PER_REV 180
#define PIN_ENC1_A	p27
#define PIN_ENC1_B	p28
#define PIN_ENC2_A	p29
#define PIN_ENC2_B	p30
#define WHEEL_RADIUS	37	//mm	
#define WHEEL_PERIMETER	0.1162389f	// WHEEL_RADIUS * PI = 0.11623892818282234982311780518134

//
//Lap Sensor Settings
//
#define INTERRUPT_PIN           0
#define CROSS_COUNTER           6


//
// Bluetooth Configs (Type here)
//
#define Bluetooth               LOG

#endif

