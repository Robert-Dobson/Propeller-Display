#include <Arduino.h>
#include "text_frames.h"
// #include "game_logic.h"
#include <time.h>

unsigned char Triangle[] = {0b00000011, 0b00001111, 0b00111111, 0b11111111, 0b11111111, 0b00111111, 0b00001111, 0b00000011};
unsigned char Square[] = {0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11111111, 0b11111111};

// Constants
const int led_pins[] = {10, 9, 8, 7, 6, 5, 4, 3};
const int num_of_leds = 8;
const int size_of_frame = 100;
const int max_game_tick_time = 300;

unsigned long int rpm, maxRPM;
const double PI_2 = M_PI * 2;
int game_tick_time = max_game_tick_time;

// Angles
double angle = 0;
double anglePerMilisecond = 120.0 / 1000; // Angle per second div by 1000
double lastUpdateTime;
int sliceIndex = 0;

int index = 0;

// Screen
unsigned char *frame = NULL;
int size = 0;

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

/*
void do_game_process()
{
  Serial.println("hi");
  GameLogic g;
  if (g.gameRunning)
  {
    g.gameTick();
    if (g.gameRunning)
    {
      frame = g.generateFrame();
      size = g.width;
    }
    else
    {
      TextFrame textFrame;
      char text[] = {'G', 'A', 'M', 'E', 'O', 'V', 'E', 'R'};
      frame = textFrame.convertStringToFrame(text);
      size = textFrame.getSize();
    }
  }
}
*/

int getSliceIndex(double angle, double maxAngle, double minAngle)
{
  // Calculate proportion through frame using angle then return correct slice of frame
  if (angle < maxAngle && angle > minAngle)
  {
    return round((angle - minAngle) / (maxAngle - minAngle) * size);
  }
  else
  {
    return -1;
  }
}

void updateAngle()
{
  double currentTime = millis();
  double timeDifference = (currentTime - lastUpdateTime);
  angle += (anglePerMilisecond * timeDifference);
  while (angle > (PI_2))
  {
    angle -= PI_2;
  }
  lastUpdateTime = currentTime;
}

void setup()
{
  // set LED pins as outputs
  // Serial.begin(9600);
  pinMode(13, INPUT);
  for (int i = 0; i < num_of_leds; i++)
  {
    pinMode(led_pins[i], OUTPUT);
  }
  
  TextFrame textFrame;
  char text[] = {' ', ' ', ' ', 'G', 'O', 'O', 'D', 'B', 'Y', 'E', '\0'};
  
  //Get length
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
  // lastUpdateTime = millis();
}

void loop()
{
  if (size != 0){
    update_leds(frame[index]);
    index++;
    if (index == size){
      index = 0;
    }
  }
}
