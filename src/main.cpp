#include <Arduino.h>

int led_pins[] = {2, 3, 4, 5, 6, 7};
const int num_of_leds = 6;
int light = 0;

unsigned long int rpm, maxRPM;

void update_leds(int led_vals[num_of_leds]){
  for (int i = 0; i < num_of_leds; i++){
    digitalWrite(led_pins[i], led_vals[i]);
  }
}

void setup() {
  // set LED pins as outputs
  Serial.begin(9600);
  pinMode(13, INPUT);
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

  // sensor
  float a = digitalRead(13);
  Serial.println(a);

}

int * calculate_leds() {

}
