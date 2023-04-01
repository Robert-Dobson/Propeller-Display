#include <Arduino.h>

int led_pins[] = {2, 3, 4, 5, 6, 7};
const int num_of_leds = 6;

void update_leds(int led_vals[num_of_leds]){
  for (int i = 0; i < num_of_leds; i++){
    digitalWrite(led_pins[i], led_vals[i]);
  }
  delay(100);
}

void setup() {
  // set LED pins as outputs
  for (int i = 0; i < num_of_leds; i++){
    pinMode(led_pins[i], OUTPUT);
  }
  
}

void loop() {
  int light[] = {1, 1, 1, 1, 1, 1};
  update_leds(light);
  int dark[] = {0, 0, 0, 0, 0, 0};
  update_leds(dark);
}

