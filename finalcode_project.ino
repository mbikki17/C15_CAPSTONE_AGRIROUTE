//#include <MemoryFree.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
//SoftwareSerial GPSSerial(A0,A1); // RX, TX  GPS  10,11
char rec=' ';
char arr_gps[200] = "";
uint8_t valid_data_gps_flag=0;
uint8_t start_gps_reading=0;
uint8_t gps_count=0;
uint8_t arr_count_gps=0;
#define TRUE   1
#define FALSE   0
char time[30];
char gps_valid;
char latitude[20];
char lat_ns;
char longitude[20];
char lon_ew;
float lat1,lon1,tem1,tem2,tem3;
unsigned long panicMillis=0;
unsigned long outofrangeMillis=0;
unsigned long connectionMillis=0;
int read_flag=0;
int connection_flag=1;
#define buzzer 11
//GSM Serial
SoftwareSerial GSerial(2,3); // RX, TX    // GSM
char aux_string[25];
char phone_number[20]="9953986150";
char SMS[400];

int Swi = 10;

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

float volt_value;

unsigned long previousMillis=5000,previousMillis1;

//*************************************************
int8_t sendATcommand2(char* ATcommand, char* expected_answer1, char* expected_answer2, unsigned int timeout)      //This function sends command to the GSM Modem and wait for reply according to arguments
{
    uint8_t x=0,  answer=0;
    char response[300];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialize the string

    delay(100);
    while( GSerial.available() > 0) GSerial.read();    // Clean the input buffer

    GSerial.println(ATcommand);    // Send the AT command 

    x = 0;
    previous = millis();

    // this loop waits for the answer
    do{
        // if there are data in the UART input buffer, reads it and checks for the asnwer
        if(GSerial.available() != 0){    
            response[x] = GSerial.read();
            x++;
            // check if the desired answer 1  is in the response of the module
            if (strstr(response, expected_answer1) != NULL)    
            {
                answer = 1;
            }
            // check if the desired answer 2 is in the response of the module
            else if (strstr(response, expected_answer2) != NULL)    
            {
                answer = 2;
            }
        }
    }
    // Waits for the asnwer with time out
    while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;
}
//*************************************************
void send_message(char *message)
{
  char aux_string[25];
  uint8_t answer=0;
  Serial.print(F("GSM : Sending SMS ..."));
  memset(aux_string, '\0', 24);    // Initialize the string
  sprintf(aux_string,"AT+CMGS=\"%s\"", phone_number);
  answer = sendATcommand2(aux_string, ">", ">", 3000);    // send the SMS number
  if (answer == 1)
  {
      GSerial.println(message);
      GSerial.write(0x1A);
      answer = sendATcommand2("", "OK", "OK", 20000);
      if (answer == 1)
      {
          Serial.println(F("Sent"));    
      }
      else
      {
          Serial.println(F("X....Error"));
      }
  }
  else
  {
      Serial.print(F("X...error "));
      Serial.println(answer, DEC);
  }
}
//*************************************************
void send_msg_location(char *message)
{
  char aux_string[50];
  uint8_t answer=0;
  Serial.print(F("GSM : Sending SMS ..."));
  memset(aux_string, '\0', 24);    // Initialize the string
  sprintf(aux_string,"AT+CMGS=\"%s\"", phone_number);
  answer = sendATcommand2(aux_string, ">", ">", 3000);    // send the SMS number
  if (answer == 1)
  {
      GSerial.print(message);GSerial.print("http://maps.google.com/maps?q=+"); GSerial.print(lat1,5);GSerial.print(",+");GSerial.print(lon1,5);
      GSerial.write(0x1A);
      answer = sendATcommand2(" ", "OK", "OK", 20000);
      if (answer == 1)
      {
//          Serial.println(F("Sent"));    
      }
      else
      {
//          Serial.println(F("X....Error"));
      }
  }
  else
  {
      Serial.print(F("X...error "));
      Serial.println(answer, DEC);
  }
}
//*************************************************
void init_gsm()
{
    uint8_t answer=0;   
    uint8_t gsm_detect_count=0; 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GSM init...");
    delay(2000);
    GSerial.begin(9600);           //UART for GSM Modem
    
    
    while((sendATcommand2("AT", "OK","OK", 2000)!=1) && (gsm_detect_count<3))      //If 3 times gsm is not connected then it is not initialized
    {
      gsm_detect_count++;
      Serial.println(F("GSM : Not Detected"));
      delay(5000);
    }
    
    if(gsm_detect_count>=3)
    {
      Serial.println(F("GSM : Finally Not Detected"));     
      Serial.println(F("GSM : System Hang"));    
      lcd.print("X");
      lcd.setCursor(0, 1);
      lcd.print("System Hang");
      while(1)
      {
        digitalWrite(buzzer,HIGH);
        delay(100);
        digitalWrite(buzzer,LOW);
        delay(100);      
      }
    }
    else
    {
      lcd.print("OK");
      Serial.println(F("GSM : Detected, Initializing"));            
      //************
      Serial.print(F("GSM : Setting SMS mode..."));
      answer = sendATcommand2("AT+CMGF=1", "OK", "OK", 1000);    // sets the SMS mode to text
      if(answer == 1)
      {
        Serial.println("OK");  
      }
      else
      {
        Serial.println("X");
      }
      //************
      Serial.print(F("GSM : Setting Baud Rate..."));
      answer = sendATcommand2("AT+IPR=9600", "OK", "OK", 1000);    // sets the SMS mode to text
      if(answer == 1)
      {
        Serial.println(F("OK"));  
      }
      else
      {
        Serial.println(F("X"));
      }
      //************    
    }  
    delay(2000);
    lcd.clear();
}
//*************************************************
void process_gps_data(char *arr)
{
  uint8_t i;
  //Get time
  i=0;
  while(*arr!=',')  
  {
    time[i++]=*arr;
    arr++;
  }
  time[i]='\0';
  
  //Get GPS_valid
  arr++;
  gps_valid=*arr;
  arr++;

  //Get latitude
  arr++;
  i=0;
  while(*arr!=',')  
  {
    latitude[i++]=*arr;
    arr++;
  }
  latitude[i]='\0';

  //Get lat_ns
  arr++;
  if(*arr==',')
  {lat_ns='\0';}
  else
  {lat_ns=*arr;
  arr++;}

  //Get longitude
  arr++;
  i=0;
  while(*arr!=',')  
  {
    longitude[i++]=*arr;
    arr++;
  }
  longitude[i]='\0';

  //Get lon_ew
  arr++;
  if(*arr==',')
  {lon_ew='\0';}
  else
  {lon_ew=*arr;
  arr++;}

  //Display GPS data on uart, for debugging only
  /*Serial.println(); 
  Serial.print("Time:");Serial.print(time);Serial.print("\r\n");
  Serial.print("Data Valid:");Serial.print(gps_valid);Serial.print("\r\n");
  Serial.print("Latitude:");Serial.print(latitude);Serial.print("\r\n");
  Serial.print("Latitude N/S:");Serial.print(lat_ns);Serial.print("\r\n");
  Serial.print("Longitude:");Serial.print(longitude);Serial.print("\r\n");
  Serial.print("Longitude E/W:");Serial.print(lon_ew);Serial.print("\r\n"); */
}
//*************************************************
void read_gps2()
{
  if(Serial.available() > 0)
  {
    rec=Serial.read();
    if(gps_count==7)
    {
      if(rec==0x0D)
      {
        gps_count=0;
        arr_gps[arr_count_gps] = '\0';
        valid_data_gps_flag=TRUE;         //Valid GPS data is received in the array
        //Serial.println();
        process_gps_data(arr_gps);
        start_gps_reading=0;
      }
      else
      {
        arr_gps[arr_count_gps++] = rec;
       // Serial.print(rec);
        //uart_tx(rec);           //Debugging on uart
      }
    }
    //***************
    if(gps_count==6)
    {
      if(rec==',')
      {
        gps_count=7;   
        //uart1_puts("\r\n");         //Debugging on uart
      }
      else
      {gps_count=0;}
    }
    //***************
    if(gps_count==5)
    {
      if(rec=='C')
      {gps_count=6;}
      else
      {gps_count=0;}
    }
    //***************
    if(gps_count==4)
    {
      if(rec=='M')
      {gps_count=5;}
      else
      {gps_count=0;}
    }
    //***************
    if(gps_count==3)
    {
      if(rec=='R')
      {gps_count=4;}
      else
      {gps_count=0;}
    }
    //***************
    if(gps_count==2)
    {
      if(rec=='P')
      {gps_count=3;}
      else
      {gps_count=0;}
    }
    //***************
    if(gps_count==1)
    {
      if(rec=='G')
      {gps_count=2;}
      else
      {gps_count=0;}
    }
    //***************
    if(rec=='$')
    {
      if(start_gps_reading==1)
      {
        gps_count=1;
        arr_count_gps=0;      // GPS data array count reset to 0
      }
    }
    //***************
    /////
  }
}
//*************************************************
void read_gps_location()
{
  lcd.clear();
  start_gps_reading=1;
  valid_data_gps_flag=FALSE;
  while(valid_data_gps_flag!=TRUE)
  {
    read_gps2();      
  }
      lat1 = atof(latitude);
      lon1 = atof(longitude);
      tem1 = (int)(lat1/100);
      tem2 = (lat1 - (tem1*100));
      tem3 = (tem2*10000)/60;
      lat1 = tem1 + (tem3/10000);
      Serial.print(F("Lat1:"));Serial.println(lat1,5);
      tem1 = (int)(lon1/100);
      tem2 = (lon1 - (tem1*100));
      tem3 = (tem2*10000)/60;
      lon1 = tem1 + (tem3/10000);
      Serial.print(F("Lon1:"));Serial.println(lon1,5);
      
  disp_gps_lcd();
  delay(1000);
}
//*************************************************
void disp_gps_lcd()
{
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LAT:");lcd.print(lat1,4);//lcd.print(latitude);lcd.print(lat_ns);
  lcd.setCursor(0, 1);
  lcd.print("LON:");lcd.print(lon1,4);//lcd.print(longitude);lcd.print(lon_ew);
  delay(2000);
}
//*************************************************
void receive_gsm_message()
{
  char *n1;
  int8_t answer;
  int x;
  unsigned long previous;
  unsigned int timeout=5000;
 // answer = sendATcommand("AT+CMGR=1", "+CMGR:", 5000);    // reads the first SMS
  answer = sendATcommand2("AT+CMGR=1", "+CMGR:", "OK", 250);    // reads the first SMS
  if(answer==1)
  {
      Serial.println(F("\nGSM : Some Message Received"));
      answer = 0;
      x=0;
      previous = millis();
      do{
          // if there are data in the UART input buffer, reads it and checks for the asnwer
          if(GSerial.available() > 0){    
              SMS[x] = GSerial.read();
              x++;
              // check if the desired answer (OK) is in the response of the module
              /*
              if (strstr(SMS, "OK") != NULL)    
              {
                  answer = 1;
              }*/
          }
      }while(answer == 0 && ((millis() - previous) < timeout));    // Waits for the asnwer with time out
      SMS[x] = '\0';
      answer = sendATcommand2("AT+CMGD=1", "OK", "OK", 500);    // sets the SMS mode to text
      /*Serial.print("Answer2 = ");
      Serial.println(answer,DEC);
      */
      Serial.print(F("GSM : Message Rec-"));Serial.println(SMS);   
      //decode_mobile_no(SMS);
      //decode_string(SMS);
      //decode_array3(SMS);
      if(strstr(SMS,"<LOC>"))
      {
        Serial.println(F("Yes, <LOC> String Present"));
        lcd.clear();
        lcd.setCursor(0, 0); 
        lcd.print(F("Received Message"));
        lcd.setCursor(0, 1); 
        lcd.print(F("Location Info"));
    delay(2000);
        read_gps_location();
        GSerial.listen();
        send_msg_location("Location : ");
        delay(5000);
    lcd.clear();
      }      
      else
      {
        Serial.println(F("No, String Not Present"));
      }
  }
  else
  {
    //Serial.println(F("GSM : Error, No Message"));
  }
}
//*************************************************
void setup() 
{ 
  Serial.begin(9600);
  //GPSSerial.begin(9600); 
  pinMode(buzzer,OUTPUT);  
  Serial.println(F("Program Started"));
  pinMode(Swi,INPUT_PULLUP);
  digitalWrite(Swi,HIGH);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); 
  lcd.print(F("GSM-GPS Tracking"));
  lcd.setCursor(0,1);
  lcd.print(F("    System      "));
  delay(5000);
  lcd.clear();
  init_gsm();
  delay(5000);
  GSerial.listen();
  send_message("System Started");
  digitalWrite(buzzer,HIGH);
  delay(2000);
  digitalWrite(buzzer,LOW);
  delay(2000);
  GSerial.listen();
  send_msg_location("Location : ");
}
//*************************************************
void loop()
{  
  lcd.setCursor(0, 0);
  lcd.print(F("System ready    "));
  lcd.setCursor(0, 1);
  lcd.print(F("                "));
  if(digitalRead(Swi)== LOW)
  {
    delay(100);
    if(digitalRead(Swi)== LOW)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("       SOS       "));
        delay(2000);  
        read_gps_location();
        GSerial.listen();
        send_msg_location("At this Location : ");
        delay(5000);
        lcd.clear();    
      }
  }
  if(millis() - previousMillis > 2000)
  {
    lcd.clear();
    GSerial.listen();
    receive_gsm_message();    
    previousMillis = millis();
  }
  delay(100); 
}
//*************************************************
