#include <Time.h>
#include <TimeLib.h>
#include <SevSeg.h>

float time;
int r, g=256, b=256;
SevSeg sevseg;

byte numDigits = 6;  // Números de dígitos usados
byte digitPins[] = {10, 9, 8, 11, 12, 13};
byte segmentPins[] = {A0, A1, A2, A3, A4, A5, 7, 22}; // Pines en arduino
  
void setup() {
  pinMode(6,OUTPUT);
  Serial.begin(9600);
  Serial.println("Simple Arduino Clock using Old DVD Player Display"); // Debug
 
  setTime(10, 30, 00, 7, 4, 18);    // HH:MM:SS MM-DD-YY

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, 1,1,1);
  sevseg.setBrightness(50);       // Actúa como limitador de corriente
}

void  loop() { 
  digitalClockDisplay();
  segmentDisplay();
  Serial.println(time);
  sevseg.refreshDisplay();
  analogWrite(3,b);
  analogWrite(5,r);
  analogWrite(6,g);
}

void digitalClockDisplay() {
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
  r=r+1;
  g=g-2;
  b=b-4;
  if (r==256 || g==256 || b==0){
    r=0;
    g=0;
    b=0;  
  }
}

void printDigits(int digits) {
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void segmentDisplay() {
  time = hour() * 0.01;
  time += minute() * 0.0001;
  time += second() * 0.000001;
  sevseg.setNumber(time, 6);
}
