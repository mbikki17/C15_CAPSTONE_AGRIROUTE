#include "hardware_config.h"

// Define global objects
DHT dht(DHT_PIN_DATA);
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_E, LCD_PIN_DB4, LCD_PIN_DB5, LCD_PIN_DB6, LCD_PIN_DB7);
HX711 scale(SCALE_PIN_DAT, SCALE_PIN_CLK);

// Define variables for testing menu
const int timeout = 10000; // Timeout of 10 sec
char menuOption = 0;
long time0;

void setup() 
{
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Start");

    dht.begin();
    lcd.begin(16, 2);
    scale.set_scale(CALIBRATION_FACTOR); 
    scale.tare();

    menuOption = menu();
}

void loop() 
{
    if (menuOption == '1') 
    {
        float dhtHumidity = dht.readHumidity();
        float dhtTempC = dht.readTempC();
        Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
        Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));
    }
    else if (menuOption == '3') 
    {
        lcd.setCursor(0, 0);
        lcd.print("Circuito Rocks !");
        lcd.noDisplay();
        delay(500);
        lcd.display();
        delay(500);
    }
    else if (menuOption == '4') 
    {
        float scaleUnits = scale.get_units();
        Serial.print(scaleUnits);
        Serial.println(" Kg");
    }

    if (millis() - time0 > timeout) 
    {
        menuOption = menu();
    }
}

char menu() 
{
    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(3) LCD 16x2"));
    Serial.println(F("(4) SparkFun HX711 - Load Cell Amplifier"));
    Serial.println(F("(menu) send anything else or press on-board reset button\n"));
    
    while (!Serial.available());
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            if (c == '1') 
                Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
            else if (c == '3') 
                Serial.println(F("Now Testing LCD 16x2"));
            else if (c == '4') 
                Serial.println(F("Now Testing SparkFun HX711 - Load Cell Amplifier"));
else 
            {
                Serial.println(F("Illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
