#include <Arduino.h>
#include "text_frames.h"
// #include "game_logic.h"
#include <time.h>

unsigned char Triangle[] = {0b00000011, 0b00001111, 0b00111111, 0b11111111, 0b11111111, 0b00111111, 0b00001111, 0b00000011};
unsigned char Square[] = {0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11111111, 0b11111111};

// Constants
const int led_pins[] = {10, 9, 8, 7, 6, 5, 4, 3};
const int num_of_leds = 8;

int index = 0;

// Screen
unsigned char *frame = NULL;
int size = 0;

// Timing of demo
unsigned long startTime = millis();
int demoSelect = 0;
const int numOfDemos = 3;
char demoWords[numOfDemos][11] = {
  {' ', ' ', ' ', ' ', ' ', 'H', 'E', 'L', 'L', 'O', '\0'},
  {' ', ' ', ' ', ' ', ' ', ' ', 'B', 'A', 'T', 'H', '\0'},
  {' ', ' ', ' ', ' ', ' ', ' ', 'H', 'A', 'C', 'K', '\0'} 
};

// Pass in a slice
void update_leds(unsigned char led_vals)
{
  for (int i = 0; i < num_of_leds; i++)
  {
    int val = (led_vals >> i) & 0x01;
    digitalWrite(led_pins[i], val);
    // Serial.print(val);
  }
  delay(1.5);
}

void updateTextFrame(char *text){
  if (frame != NULL){
    free(frame);
    frame = NULL;
  }

  TextFrame textFrame;

  //Get length and reverse
  int index = 0;
  while (text[index] != '\0'){
    index++;
  }
  int length = index;

  char reversetext[length+1];
  for (int i = length-1; i >= 0; i--){
    reversetext[(length-1)-i] = text[i];
  }
  reversetext[length] = '\0';

  frame = textFrame.convertStringToFrame(reversetext);
  size = textFrame.getSize();
}


void setup()
{
  // set LED pins as outputs
  pinMode(13, INPUT);
  for (int i = 0; i < num_of_leds; i++)
  {
    pinMode(led_pins[i], OUTPUT);
  }

  updateTextFrame(demoWords[0]);
}


void loop()
{
  unsigned long timeDif = millis() - startTime;
  if (timeDif >= 10000){
    demoSelect++;

    if (demoSelect == numOfDemos){
      demoSelect = 0;
    }

    updateTextFrame(demoWords[demoSelect]);
    startTime = millis();
  }

  if (size != 0){
    update_leds(frame[index]);
    index++;
    if (index == size){
      index = 0;
    }
  }
}
