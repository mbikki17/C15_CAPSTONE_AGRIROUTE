// source.h - Function Definitions for GPS-GSM Tracking System
#include "inc.h"

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
SoftwareSerial GSerial(2, 3); // RX, TX for GSM Module

char rec = ' ';
char arr_gps[200] = "";
uint8_t valid_data_gps_flag = 0, start_gps_reading = 0, gps_count = 0, arr_count_gps = 0;
char time[30], gps_valid, latitude[20], lat_ns, longitude[20], lon_ew;
float lat1, lon1, tem1, tem2, tem3;
unsigned long panicMillis = 0, outofrangeMillis = 0, connectionMillis = 0;
int read_flag = 0, connection_flag = 1;
char aux_string[25], phone_number[20] = "phoneno", SMS[400];
float volt_value;
unsigned long previousMillis = 5000, previousMillis1;

// Send AT command to GSM module and wait for a response
int8_t sendATcommand2(char* ATcommand, char* expected_answer1, char* expected_answer2, unsigned int timeout) {
    uint8_t x = 0, answer = 0;
    char response[300];
    unsigned long previous;

    memset(response, '\0', 100);
    delay(100);
    while (GSerial.available() > 0) GSerial.read();

    GSerial.println(ATcommand);
    previous = millis();

    do {
        if (GSerial.available() != 0) {
            response[x++] = GSerial.read();
            if (strstr(response, expected_answer1) != NULL) answer = 1;
            else if (strstr(response, expected_answer2) != NULL) answer = 2;
        }
    } while ((answer == 0) && ((millis() - previous) < timeout));

    return answer;
}

// Send SMS
void send_message(char *message) {
    char aux_string[25];
    uint8_t answer;
    Serial.print(F("GSM : Sending SMS ..."));
    sprintf(aux_string, "AT+CMGS=\"%s\"", phone_number);
    answer = sendATcommand2(aux_string, ">", ">", 3000);
    if (answer == 1) {
        GSerial.println(message);
        GSerial.write(0x1A);
        if (sendATcommand2("", "OK", "OK", 20000) == 1) Serial.println(F("Sent"));
        else Serial.println(F("X....Error"));
    } else {
        Serial.print(F("X...error "));
        Serial.println(answer, DEC);
    }
}

// Send GPS Location via SMS
void send_msg_location(char *message) {
    char aux_string[50];
    uint8_t answer;
    Serial.print(F("GSM : Sending SMS ..."));
    sprintf(aux_string, "AT+CMGS=\"%s\"", phone_number);
    answer = sendATcommand2(aux_string, ">", ">", 3000);
    if (answer == 1) {
        GSerial.print(message);
        GSerial.print("http://maps.google.com/maps?q=+");
        GSerial.print(lat1, 5);
        GSerial.print(",+");
        GSerial.print(lon1, 5);
        GSerial.write(0x1A);
    }
}

// Initialize GSM module
void init_gsm() {
    uint8_t answer, gsm_detect_count = 0;
    lcd.clear();
    lcd.print("GSM init...");
    delay(2000);
    GSerial.begin(9600);

    while ((sendATcommand2("AT", "OK", "OK", 2000) != 1) && (gsm_detect_count < 3)) {
        gsm_detect_count++;
        Serial.println(F("GSM : Not Detected"));
        delay(5000);
    }

    if (gsm_detect_count >= 3) {
        Serial.println(F("GSM : Finally Not Detected"));
        lcd.print("X");
        lcd.setCursor(0, 1);
        lcd.print("System Hang");
        while (1) {
            digitalWrite(buzzer, HIGH);
            delay(100);
            digitalWrite(buzzer, LOW);
            delay(100);
        }
    } else {
        lcd.print("OK");
        Serial.println(F("GSM : Detected, Initializing"));
        sendATcommand2("AT+CMGF=1", "OK", "OK", 1000);
        sendATcommand2("AT+IPR=9600", "OK", "OK", 1000);
    }
    delay(2000);
    lcd.clear();
}

// Process GPS Data
void process_gps_data(char *arr) {
    uint8_t i = 0;
    while (*arr != ',') time[i++] = *arr++;
    time[i] = '\0';
    gps_valid = *(++arr);
    arr++;
    while (*arr != ',') latitude[i++] = *arr++;
    latitude[i] = '\0';
}

// Read GPS Location
void read_gps_location() {
    lcd.clear();
    start_gps_reading = 1;
    valid_data_gps_flag = FALSE;
    while (valid_data_gps_flag != TRUE) read_gps2();
    lat1 = atof(latitude);
    lon1 = atof(longitude);
    disp_gps_lcd();
    delay(1000);
}

// Display GPS on LCD
void disp_gps_lcd() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LAT:");
    lcd.print(lat1, 4);
    lcd.setCursor(0, 1);
    lcd.print("LON:");
    lcd.print(lon1, 4);
    delay(2000);
}

