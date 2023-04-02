#include <Arduino.h>
#include <time.h>
#include "text_frames.h"



unsigned char Triangle[] = {0b00000011, 0b00001111, 0b00111111, 0b11111111, 0b11111111, 0b00111111, 0b00001111, 0b00000011};
unsigned char Square[] = {0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11111111, 0b11111111};

// Constants
const int led_pins[] = {10, 9, 8, 7, 6, 5, 4, 3};
const int num_of_leds = 8;

int index = 0;

// Screen
unsigned char *frame = NULL;
int size = 0;
unsigned char wave[9] = {0b00000000, 0b00000001,  0b00000011, 0b00000110,  0b00001100, 0b00011000,  0b00110000, 0b01100000, 0b11000000};
bool increasing_wave = true;

// Timing of demo
unsigned long startTime = millis();
int demoSelect = -1;
const int numOfDemos = 6;
char demoWords[numOfDemos][11] = {
  {' ', ' ', ' ', ' ', ' ', 'H', 'E', 'L', 'L', 'O', '\0'},
  {' ', ' ', ' ', ' ', ' ', ' ', 'B', 'A', 'T', 'H', '\0'},
  {' ', ' ', ' ', ' ', ' ', ' ', 'H', 'A', 'C', 'K', '\0'}, 
  {' ', ' ', ' ', ' ', ' ', ' ', 'V', 'O', 'T', 'E', '\0'},
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'F', 'O', 'R', '\0'},
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'U', 'S', '\0'},
};

// Pass in a slice
void update_leds(unsigned char led_vals, float time_delay = 1.6)
{
  for (int i = 0; i < num_of_leds; i++)
  {
    int val = (led_vals >> i) & 0x01;
    digitalWrite(led_pins[i], val);
    // Serial.print(val);
  }
  delay(time_delay);
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

  
  Serial.println(reversetext);
  frame = textFrame.convertStringToFrame(reversetext);
  size = textFrame.getSize();
}


void updateFrameText(char *text){
  if (frame != NULL){
    free(frame);
  }
  
  TextFrame textFrame;
  frame = textFrame.convertStringToFrame(text);
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
}

void textLoop(){
  startTime = millis();
  bool loop = true;
  
  while (loop){
    unsigned long timeDif = millis() - startTime;
    if (timeDif >= 7500 || demoSelect == -1){
      demoSelect++;

      if (demoSelect == numOfDemos){
        demoSelect = -1;
        loop = false;
        break;
      }
      else{
        updateTextFrame(demoWords[demoSelect]);
        startTime = millis();
      }
    }

    if (loop != false){
      if (size != 0){
        update_leds(frame[index]);
        index++;
        if (index == size){
          index = 0;
        }
      }
    }
  }
  
}


void loop()
{
  // Triangles and Squares
  for (int n = 0; n < 300; n ++){
    for (int i = 0; i < 8; i++){
      update_leds(Triangle[i], 2);
    }
    update_leds(0, 2);
    update_leds(0, 2);
    for (int i = 0; i < 8; i++){
      update_leds(Square[i], 2);
    }
    update_leds(0, 2);
    update_leds(0, 2);
  }
  

  // Text
  textLoop();
  
  // Wave
  for (int n = 0; n < 6; n += 1){
    for (int i = 0; i < 9; i+=1){
      update_leds(wave[i], n * 20);
    }
    for (int j = 8; j >= 0; j-=1){
      update_leds(wave[j], n * 20);
    }
  }
  
  for (int n = 5; n >=0; n -= 1){
    for (int i = 0; i < 9; i+=1){
      update_leds(wave[i], n * 20);
    }
    for (int j = 8; j >= 0; j-=1){
      update_leds(wave[j], n * 20);
    }
  }
  
}
