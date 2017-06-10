#ifndef CONFIG_H
#define CONFIG_H
#include "mbed.h"

//
// Project
//
#define PROJECT_NAME            F("Neo Follower Firmware")
#define PROJECT_VERSION         F("v0.4")


//
// Interface (Buzzer/Leds)
//
#define PIN_BUZZER              10
#define PIN_JOYSTICK            A3


//
// Serial DEBUG
//
#define SERIAL_SPEED            115200
#define LOG                     Serial.print


//
// Stick Settings
//
#define STICK_RELEASED          254
#define STICK_UP                17
#define STICK_LEFT              3
#define STICK_DOWN              42
#define STICK_RIGHT             30
#define STICK_CENTER            52

//
// Line Reader Settings
//

#define PIN_LR_S0								p15
#define PIN_LR_S1   	          p16
#define PIN_LR_S2 	            p17
#define PIN_LR_S3     	        p18
#define PIN_LR_S4								p19
#define PIN_LR_S5								p20
#define PIN_TRACK_MARKING_RIGHT	p13							
#define PIN_TRACK_MARKING_LEFT	p14



//
// Motors config (H-Bridge)
//
#define PWM_PERIOD              1/90000 //Maximo 100KHz
#define MOTOR_ABS_MAX           255
#define PIN_M1_EN               p26
#define PIN_M1_IN1              p5
#define PIN_M1_IN2              p6

#define PIN_M2_EN               p27
#define PIN_M2_IN1              p7
#define PIN_M2_IN2              p8


//
//Lap Sensor Settings
//
#define INTERRUPT_PIN           0
#define CROSS_COUNTER           6


//
// VBat Reader (battery status)
//
#define VBAT_ALARMED            7.10
#define VBAT_WARNED             7.40

#define PIN_VBAT                A4
#define VBAT_VOLTAGE(adc)       (adc - 534) * (8.23 - 6.47) / (662-534) + 6.47
// ((adc - 40.3) / 88.3)


//
// Bluetooth Configs (Type here)
//
#define Bluetooth               Serial



#endif
