// test.h - Main Program Logic
#include "inc.h"
#include "source.h"

void setup() {
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    pinMode(Swi, INPUT_PULLUP);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("GSM-GPS Tracking");
    delay(5000);
    lcd.clear();
    init_gsm();
    GSerial.listen();
    send_message("System Started");
}

void loop() {
    lcd.setCursor(0, 0);
    lcd.print(F("System ready"));
    if (digitalRead(Swi) == LOW) {
        delay(100);
        if (digitalRead(Swi) == LOW) {
            lcd.clear();
            lcd.print(F("SOS"));
            delay(2000);
            read_gps_location();
            GSerial.listen();
            send_msg_location("At this Location: ");
        }
    }
    if (millis() - previousMillis > 2000) {
        lcd.clear();
        GSerial.listen();
        receive_gsm_message();
        previousMillis = millis();
    }
}

