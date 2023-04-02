/*
#include <Arduino.h>

float start;
float last = 0;
unsigned long firstTime;
unsigned long startTime;
unsigned long endTime;


void setup() 
{ 
  Serial.begin(9600);
  pinMode(A3, INPUT);
  start = analogRead(A3);
  firstTime = millis();
  startTime = firstTime;
} 

void loop() 
{ 
  // sensor
  float a = analogRead(A3);

  if (a > start + 1){
    if (startTime == firstTime){
      startTime = millis();
    }
    else{
      endTime = millis();
      unsigned long timeDif = endTime - startTime;
      if (timeDif > 25){
        Serial.println(timeDif);
      }
      startTime = millis();
    }
  }  
}
*/