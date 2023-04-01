#include <Arduino.h>

int led_pins[] = {2, 3, 4, 5, 6, 7};
int RPM = 500;
const int num_of_leds = 6;
int light = 0;

void update_leds(int led_vals[num_of_leds]){
  for (int i = 0; i < num_of_leds; i++){
    digitalWrite(led_pins[i], led_vals[i]);
  }
}

void setup() {
  // set LED pins as outputs
  for (int i = 0; i < num_of_leds; i++){
    pinMode(led_pins[i], OUTPUT);
  }
  
}

void loop() {
  int lights[] = {0, 0, 0, 0, 0, 0};
  lights[light] = 1;
  update_leds(lights);
  light++;
  if (light > 5) {
    light = 0;
  }
}

int * calculate_leds() {

}
