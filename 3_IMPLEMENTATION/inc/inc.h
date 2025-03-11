// inc.h - Header file for GPS-GSM Tracking System

#ifndef INC_H
#define INC_H

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Pin Definitions
#define buzzer 11
#define Swi 10
#define TRUE 1
#define FALSE 0

// Global Variables
extern char rec;
extern char arr_gps[200];
extern uint8_t valid_data_gps_flag, start_gps_reading, gps_count, arr_count_gps;
extern char time[30], gps_valid, latitude[20], lat_ns, longitude[20], lon_ew;
extern float lat1, lon1, tem1, tem2, tem3;
extern unsigned long panicMillis, outofrangeMillis, connectionMillis;
extern int read_flag, connection_flag;
extern char aux_string[25], phone_number[20], SMS[400];
extern float volt_value;
extern unsigned long previousMillis, previousMillis1;

// LCD & Serial Communication
extern LiquidCrystal lcd;
extern SoftwareSerial GSerial;

// Function Prototypes
int8_t sendATcommand2(char* ATcommand, char* expected_answer1, char* expected_answer2, unsigned int timeout);
void send_message(char *message);
void send_msg_location(char *message);
void init_gsm();
void process_gps_data(char *arr);
void read_gps2();
void read_gps_location();
void disp_gps_lcd();
void receive_gsm_message();

#endif
