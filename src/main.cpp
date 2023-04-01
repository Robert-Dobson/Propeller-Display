#include <Arduino.h>
#include "text_frames.h"
#include <time.h>

// Constants
const int led_pins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int num_of_leds = 8;
const int size_of_frame = 100;

//Angles
double angle = 0;
double anglePerSecond = 6;
clock_t lastUpdateTime;
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
  }
}

// Testing only
void print_frame(unsigned char *frame, int size)
{
  // change to update with angle
  for (int i = 0; i < size; i++)
  {
    update_leds(frame[i]);
  }
}

// void print_text(char *text)
// {
//   TextFrame textFrame;
//   char text[] = {'H', 'E', 'S', 'T'};
//   frame = textFrame.convertStringToFrame("Hello");
//   size = textFrame.getSize();

//   print_frame(frame, size);
//   delay(1000000);

//   // Free
//   free(frame);
//   frame = NULL;
// }

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
  clock_t currentTime = clock();
  double timeDifference = (currentTime - lastUpdateTime);
  angle += (anglePerSecond * timeDifference / 1000);
  while (angle > (2 * M_PI))
  {
    angle -= 2 * M_PI;
  }
  lastUpdateTime = currentTime;
}

void setup()
{
  // set LED pins as outputs
  for (int i = 0; i < num_of_leds; i++)
  {
    pinMode(led_pins[i], OUTPUT);
  }
  TextFrame textFrame;
  char text[] = {'T', 'E', 'S', 'T'};
  frame = textFrame.convertStringToFrame(text);
  size = textFrame.getSize();
  lastUpdateTime = clock();
}

void loop()
{
  update_leds(frame[sliceIndex]);
  // Delay for framerate
  updateAngle();
  //sliceIndex = getSliceIndex(angle, (3 * M_PI) / 2, M_PI / 2);
  sliceIndex = getSliceIndex(angle, 0, 2 * M_PI);
}