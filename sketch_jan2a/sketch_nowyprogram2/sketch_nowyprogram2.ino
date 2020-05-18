//Biblioteki

#include <LiquidCrystal.h> //Dołączenie bilbioteki
#include<Wire.h>
#include<SPI.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_BME280.h>

//definiowanie pinów od czujnika temperatury
#define BME_SCK 13
#define BME_MISO 12
#define BME_CS 10
#define BME_MOSI 11
//Zmienne
float Temp;
float Hum;
float Press;

int Dust;
int measurePin = 0;
int ledPower = 2;
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0; 

#define SEALEVELPRESSURE_HPA (1013.25)
#define ALTITUDE 100.0
Adafruit_BME280 bme(BME_CS);
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

void setup() {
Serial.begin(9600);
Serial.println(F("Siema!")); //!!!
pinMode(ledPower,OUTPUT);
lcd.begin(16,2);

bool status;
status=bme.begin();
if(!status)
{
 lcd.print("Ups, coś poszło nie tak");
 while (1);
lcd.setCursor(7,0) ;
lcd.print("OK");
delay(1000);
}
lcd.setCursor(3,1);
lcd.print("is today?");
lcd.setCursor(2,0);
lcd.print("WhatWeather");
delay(5000);
lcd.clear();
}
void loop(){
lcd.display(); //Włącz i poczekaj
Temp = bme.readTemperature();
Press = bme.readPressure();
Press = bme.seaLevelForAltitude(ALTITUDE,Press);
Hum = bme.readHumidity();
digitalWrite(ledPower,LOW);
delayMicroseconds(sleepTime);
voMeasured = analogRead(measurePin);
delayMicroseconds(deltaTime);
digitalWrite(ledPower,HIGH);
delayMicroseconds(sleepTime);
calcVoltage = voMeasured * (5.0 / 1024.0);
dustDensity = 170 * calcVoltage - 0.1;
Serial.println(dustDensity);

lcd.setCursor(1,0);
lcd.print("Loading data");
lcd.setCursor(6,1);
lcd.print(".");
delay(350);
lcd.setCursor(1,0);
lcd.print("Loading data");
lcd.setCursor(7,1);
lcd.print(".");
delay(350);
lcd.setCursor(1,0);
lcd.print("Loading data");
lcd.setCursor(8,1);
lcd.print(".");
delay(350);
lcd.clear();

lcd.setCursor(1,0);
lcd.print("Loading data");
lcd.setCursor(6,1);
lcd.print(".");
delay(350);
lcd.setCursor(1,0);
lcd.print("Loading data");
lcd.setCursor(7,1);
lcd.print(".");
delay(350);
lcd.setCursor(1,0);
lcd.print("Loading data");
lcd.setCursor(8,1);
lcd.print(".");
delay(350);
lcd.clear();

lcd.setCursor(1,0);
lcd.print("Loading data");
lcd.setCursor(6,1);
lcd.print(".");
delay(350);
lcd.setCursor(1,0);
lcd.print("Loading data");
lcd.setCursor(7,1);
lcd.print(".");
delay(350);
lcd.setCursor(1,0);
lcd.print("Loading data");
lcd.setCursor(8,1);
lcd.print(".");
delay(350);
lcd.clear();



lcd.setCursor(2,0);
lcd.print("Temperature: ");
lcd.setCursor(3,1);
lcd.print(Temp);
lcd.print(" st.C");
delay(3000);
lcd.clear(); 

lcd.setCursor(3,0);
lcd.print("Pressure: ");
lcd.setCursor(2,1);
lcd.print(Press/100);
lcd.print(" hPa");
delay(3000);
lcd.clear();

lcd.setCursor(3,0);
lcd.print("Humidity: ");
lcd.setCursor(4,1);
lcd.print(Hum);
lcd.print(" %");
delay(3000);
lcd.clear();

lcd.setCursor(5,0);
lcd.print("Dust: ");
lcd.setCursor(3,1);
lcd.print(dustDensity);
lcd.print(" ug/m3");
delay(3000);
lcd.clear(); 
}
