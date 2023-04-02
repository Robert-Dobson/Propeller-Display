#include <Arduino.h>
#include "text_frames.h"
#include "game_logic.h"
#include <time.h>

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
double anglePerMilisecond = 100.0 / 1000; // Angle per second div by 1000
double lastUpdateTime;
int sliceIndex = 0;

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
}

void do_game_process()
{
  GameLogic g;
  if (g.gameRunning)
  {
    g.gameTick();
    if (g.gameRunning)
    {
      free(frame);
      frame = g.generateFrame();
      size = g.width;

      //TEST
      // for (int i = 0; i < num_of_leds; i++)
      // {
      //   for (int j = 0; j < size; j++)
      //   {
      //     int val = (frame[j] >> i) & 0x01;
      //     if (val == 1)
      //     {
      //       Serial.print("*");
      //     }
      //     else
      //     {
      //       Serial.print(" ");
      //     }
      //   }
      //   Serial.println();
      // }
      // Serial.println("\n\n\n");
    }
    else
    {
      Serial.println("Game over");
      TextFrame textFrame;
      char text[] = {'G', 'A', 'M', 'E', 'O', 'V', 'E', 'R'};
      frame = textFrame.convertStringToFrame(text);
      size = textFrame.getSize();
    }
  }
}

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
  Serial.begin(9600);
  pinMode(13, INPUT);
  for (int i = 0; i < num_of_leds; i++)
  {
    pinMode(led_pins[i], OUTPUT);
  }
  // TextFrame textFrame;
  // char text[] = {'B', 'C', 'S', 'S'};
  // frame = textFrame.convertStringToFrame(text);
  // size = textFrame.getSize();
  // lastUpdateTime = millis();
}

void loop()
{
  if (sliceIndex == -1)
  {
    update_leds(0);
  }
  else
  {
    update_leds(frame[sliceIndex]);
    // Serial.println(sliceIndex);
  }
  // Delay for framerate
  updateAngle();
  // sliceIndex = getSliceIndex(angle, (3 * M_PI) / 2, M_PI / 2);
  sliceIndex = getSliceIndex(angle, PI_2, 0);
  // sensor
  // float a = digitalRead(13);
  // Serial.println(a);
  // Tick speed
  // delay(1);
  // game
  game_tick_time--;
  if (game_tick_time <= 0)
  {
    game_tick_time = max_game_tick_time;
    do_game_process();
  }
}
