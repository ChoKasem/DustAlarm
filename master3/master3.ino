#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int buzzer = 9;
const int POT = A0;
int measurePin = A1;
int ledPower = 12;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 5000;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

float refValue = 0;

void setup(){
  Serial.begin(9600);
  lcd.begin();
  pinMode(ledPower,OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.backlight();
}

void loop(){
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  refValue = analogRead(POT);
  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = (0.17*calcVoltage-0.1)*1000;

  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }
//
//  Serial.println("Raw Signal Value (0-1023):");
//  Serial.println(voMeasured);

//  Serial.println("Voltage:");
//  Serial.println(calcVoltage);
//
  Serial.println("Dust Density:");
  Serial.println(dustDensity);
  print_lcd(dustDensity, refValue, lcd);
  if(dustDensity > refValue){
    tone(buzzer, 1000); // Send 1KHz sound signal...
//    delay(1000);        // ...for 1 sec
//    noTone(buzzer);     // Stop sound...
//    delay(1000);
  }
  else{
    noTone(buzzer);
  }
  delay(500);
}

void print_lcd(float curr, float ref, LiquidCrystal_I2C lcd)
{
  lcd.setCursor(0,0);
  String refstr = String(ref);
  String currstr = String(curr);
  lcd.print("DustLv:");
  lcd.print(currstr);
  lcd.setCursor(0,1);
  lcd.print("Ref(ug/m3):");
  lcd.print(refstr);
}
