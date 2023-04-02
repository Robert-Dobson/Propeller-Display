/*
#include <Arduino.h>
#include <math.h>

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
      if (timeDif > 20){
        Serial.println((2 * M_PI * 1000) /timeDif);
      }
      startTime = millis();
    }
  }  
}
*/