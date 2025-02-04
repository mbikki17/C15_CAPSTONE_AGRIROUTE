// Include Libraries
#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

#include "Arduino.h"
#include "DHT.h"
#include "LiquidCrystal.h"
#include "HX711.h"

// Pin Definitions
#define DHT_PIN_DATA  4
#define GPS_PIN_TX  11
#define GPS_PIN_RX  10
#define LCD_PIN_RS  12
#define LCD_PIN_E 9
#define LCD_PIN_DB4 5
#define LCD_PIN_DB5 6
#define LCD_PIN_DB6 7
#define LCD_PIN_DB7 8
#define SCALE_PIN_DAT A3
#define SCALE_PIN_CLK 13
#define SIM800L_SOFTWARESERIAL_PIN_TX 2
#define SIM800L_SOFTWARESERIAL_PIN_RX 3
// Object initialization
extern DHT dht;
extern LiquidCrystal lcd;
extern HX711 scale;

// Calibration factor for scale
#define CALIBRATION_FACTOR 2280 

// Function prototypes
char menu();

#endif // HARDWARE_CONFIG_H


