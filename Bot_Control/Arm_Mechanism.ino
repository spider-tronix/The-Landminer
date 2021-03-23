#include <Servo.h>
#include <SD.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int GPS_Button = 7;
const int Scan_Button = 8;
static const int RXPin = 2, TXPin = 1;
static const uint32_t GPSBaud = 4800;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

File GPS_Data;
int pinCS = 10; 
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int k = 54;
int pos_x = 0;
int thetha_r;
int thetha_l;

void setup() {
  // put your setup code here, to run once
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(90);

  pinMode(7,INPUT);
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  
  
  GPS_Data = SD.open("Mine_coordinates.txt", FILE_WRITE);
  
  
  if (GPS_Data) {
    Serial.println("Checking...");
    // Write to file
    GPS_Data.println("Mine_Data");
    GPS_Data.close(); // close the file
  }
 
  else {
    Serial.println("Error opening Mine_coordinates.txt");
  }
  // Reading the file
 /* GPS_Data = SD.open("Mine_coordinates.txt");
  if (GPS_Data) {
    Serial.println("Read:");
    
    while (GPS_Data.available()) {
      Serial.write(GPS_Data.read());
   }
    GPS_Data.close();
  }
  else {
    Serial.println("Error opening Mine_coordinates.txt");*/
}

void loop() 
{ 
 if(Scan_Button == HIGH)
 {
  while(k<=162)
  {
    arm_mechanism();
  }
  k=54;
  for(pos_x=162;pos_x>=0;pos_x--)
  {
    servo1.write(pos_x);
    delay(10);
    servo3.write(pos_x);
    delay(10);
  }
  for(thetha_r=90,thetha_l=0;(thetha_r>=0)&(thetha_l<=90);thetha_r--,thetha_l++)
  {
    servo2.write(thetha_r);
    delay(10);
    servo4.write(thetha_l);
    delay(10);
  }
 }
}
void arm_mechanism()
{
    for(;pos_x<=k;pos_x++)
    { 
      servo1.write(pos_x);
      if(GPS_Button == HIGH)
      delay(50);
      servo3.write(pos_x);
      if(GPS_Button == HIGH)
      delay(50);
    }
    if(k == 54 | k == 162)
    {
      for(thetha_r=0,thetha_l=90;(thetha_r<=90)&(thetha_l>=0);thetha_r++,thetha_l--)
      {
        servo2.write(thetha_r);
        if(GPS_Button == HIGH)
        delay(50);
        servo4.write(thetha_l);
        if(GPS_Button == HIGH)
        delay(50);
      }
    }

    else 
    {
      for(thetha_r=90,thetha_l=0;(thetha_r>=0)&(thetha_l<=90);thetha_r--,thetha_l++)
      {
        servo2.write(thetha_r);
        if(GPS_Button == HIGH)
        delay(50);
        servo4.write(thetha_l);
        if(GPS_Button == HIGH)
        delay(50);
      }
    }
    pos_x=k;
    k=k+54;
}

void GPS()
{
  while (ss.available() > 0)
  { 
    if(gps.encode(ss.read()))
    
      GPS_Data.write(gps.location.lat());
      GPS_Data.write(",");
     
      GPS_Data.write(gps.location.lng());
      GPS_Data.write(",");
      GPS_Data.write("\n"); 
  }
}
