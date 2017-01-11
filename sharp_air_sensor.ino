#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 2;   //Connect 3 led driver pins of dust sensor to Arduino D2
 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 
void setup(){
 
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
 
  lcd.init();                     
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("Boot...");
  lcd.setCursor(0, 1);
  for(int i=0;i<16;i++)
  {
    lcd.write(0xff);
    delay(250);
  }
  lcd.init();
  lcd.setCursor(7,1);
  lcd.print("-mg/m^3");                     
  lcd.setCursor(0, 0);
  lcd.print("air dust density");
}
 
void loop(){
  digitalWrite(ledPower,LOW); 
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin); // read the dust value
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); 
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 0.17 * calcVoltage - 0.1;
  if(dustDensity<0)dustDensity=0;
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
 
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
 
  Serial.print(" - Dust Density: ");
  Serial.println(dustDensity); // unit: mg/m3
 
//  lcd.init();                     
//  lcd.backlight();
//  lcd.setCursor(0, 0);
//  lcd.print("dustDensity:");
  lcd.setCursor(3,1);
  lcd.print(dustDensity);
 
  delay(5000);
}
