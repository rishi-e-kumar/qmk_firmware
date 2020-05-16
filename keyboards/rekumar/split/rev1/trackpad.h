#pragma once

#include "pointing_device.h"
#include "quantum.h"
#include "report.h"
#include <util/delay.h>
#include "../../lib/lufa/LUFA/Drivers/Peripheral/SPI.h"
// #include "bitmanip.h"

// Trackpad speed adjustments
#define POINTER_SPEED_MULTIPLIER 3
#define SCROLL_SPEED_MULTIPLIER 0.3

// Masks for Cirque Register Access Protocol (RAP)
#define WRITE_MASK  0x80
#define READ_MASK   0xA0

// Register config values for this demo
#define SYSCONFIG_1   0x00
#define FEEDCONFIG_1  0x03
#define FEEDCONFIG_2  0x18
#define Z_IDLE_COUNT  0x05
#define FILLER		  0xFC
#define ERA_VALUE         0x1B
#define ERA_HIGH_BYTE     0x1C
#define ERA_LOW_BYTE      0x1D
#define ERA_CONTROL       0x1E
// Coordinate scaling values
#define PINNACLE_XMAX     3581    // max value Pinnacle can report for X
#define PINNACLE_YMAX     4093    // max value Pinnacle can report for Y
#define PINNACLE_X_LOWER  100     // min "reachable" X value
#define PINNACLE_X_UPPER  3481    // max "reachable" X value
#define PINNACLE_Y_LOWER  100      // min "reachable" Y value
#define PINNACLE_Y_UPPER  3993    // max "reachable" Y value
#define PINNACLE_X_RANGE  (PINNACLE_X_UPPER-PINNACLE_X_LOWER)
#define PINNACLE_Y_RANGE  (PINNACLE_Y_UPPER-PINNACLE_Y_LOWER)
#define PINNACLE_Z_THRESHOLD 15 //minimum capacitance value to count reading
#define MOVING_AVERAGE_WINDOW 20
// Pins on corresponding ports
#define TP_CS        2 //D2 on Pro Micro
#define TP_DR		 3 //D3 on Pro Micro

// Configure as output
#define TP_CS_INIT      DDRD |= (1 << TP_CS);

// Configure as input
#define TP_DR_INIT	    DDRD &= ~(1 << TP_DR)

// Define common operations
#define TP_CS_HI        PORTD |= (1 << TP_CS);
#define TP_CS_LO        PORTD &= ~ (1 << TP_CS);
#define TP_DR_READ		PIND & (1 << TP_DR)