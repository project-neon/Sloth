#ifndef CONFIG_H
#define CONFIG_H
#include "Arduino.h"

//
// Project
//
#define PROJECT_NAME            "Sloth Firmware"
#define PROJECT_BOARD           "Maple Mini"
#define PROJECT_VERSION         "v0.0"


// Interface
#define PIN_BTN 32
#define PIN_LED 33

//
// Serial DEBUG
//
#define LOG_ENABLED true
#define LOG if(LOG_ENABLED) BT
#define PC_SPEED  115200
#define LOG_INTERVAL  0.01 //

//
// Bluetooth Configs (Type here)
//
#define BT Serial3
#define BT_SPEED  115200
#define BTRX  1
#define BTTX  0

//
// Line Reader Settings
//
#define WHITE_LINE  true
#define NUM_SENSORS 8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  1  // average 4 analog samples per sensor reading
#define EMITTER_PIN 12  // emitter is controlled by digital pin 2
#define PIN_LR_S1 11  // AIN0
#define PIN_LR_S2 10  // AIN1
#define PIN_LR_S3 9   // AIN2
#define PIN_LR_S4 8   // AIN3
#define PIN_LR_S5 7   // AIN4
#define PIN_LR_S6 6   // AIN5
#define PIN_LR_S7 5   // AIN6
#define PIN_LR_S8 4   // AIN7


//
// VBat Reader
//
#define PIN_BAT_SENSE 3   // AIN8
#define BAT_R1                 22000
#define BAT_R2                 10000
#define BAT_DROP               0.04
#define VBAT_VOLTAGE(adc)      (adc / (4096 / 3.3)) * (BAT_R1 + BAT_R2) * (1.0 / BAT_R2) + BAT_DROP

#define VBAT_ALARMED           6.90
#define VBAT_WARNED            7.10
#define VBAT_USB               5.10

//
//Lap Sensor Settings
//
#define CROSS_COUNTER 6
#define PIN_TRACK_MARKING_RIGHT 13
#define PIN_TRACK_MARKING_LEFT  14

//
// General Settings
//
#define STOP_BY_TIME false
#define LAP_TIME 20 //in seconds
#define STOP_BY_DISTANCE true
#define FINAL_TARGET_POSITION   24.00  // in meters
// #define FINAL_TARGET_POSITION   1.5
#define ACCELERATION_ENABLED true
#define ACCELERATION_INTERVAL 0.01
#define MAPPING_ENABLED false
#define FIRST_MARK_POSITION 0.5

//
//Marking Settings
//

//
// Motors config (H-Bridge)
//
#define REVERSE 0.00
#define PIN_M1_PWM  27
#define PIN_M1_IN1  28
#define PIN_M1_IN2  29
#define PIN_M2_PWM  26
#define PIN_M2_IN1  30
#define PIN_M2_IN2  31

//
// Encoder config (Quadrature)
//
#define PULSES_PER_REV 179.0 // 30:1
// #define PULSES_PER_REV 61.0 // 10:1
#define PIN_ENC1_A  22
#define PIN_ENC1_B  21
#define PIN_ENC2_A  20
#define PIN_ENC2_B  19
//#define M_PI 3.14159
#define WHEEL_RADIUS 0.020  // D = 40mm
#define WHEEL_PERIMETER (2.0*WHEEL_RADIUS*M_PI) // WHEEL_RADIUS * PI
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

#define TRACK_EVENT_NAME HACKPULICA
#define GAIN_NUMBER k1

#endif

