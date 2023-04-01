#include <Arduino.h>
#include "text_frames.h"

// Constants
const int led_pins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int num_of_leds = 8;
const int size_of_frame = 100;

// Screen
unsigned char *frame = NULL;
int size = 0;

void update_leds(unsigned char led_vals){
  for (int i = 0; i < num_of_leds; i++){
    int val = (led_vals >> i) & 0x01;
    digitalWrite(led_pins[i], val);
  }
}

void print_frame(unsigned char *frame, int size){
  // change to update with angle
  for (int i = 0; i < size; i++)
  {
    update_leds(frame[i]);
  }
}

void print_text(char *text){
  TextFrame textFrame;
  frame = textFrame.convertStringToFrame("Hello");
  size = textFrame.getSize();
  
  print_frame(frame, size);
  delay(1000000);

  // Free 
  free(frame);
  frame = NULL;
}

void setup() {
  // set LED pins as outputs
  for (int i = 0; i < num_of_leds; i++){
    pinMode(led_pins[i], OUTPUT);
  }
}

void loop() {

}