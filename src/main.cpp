#include <Arduino.h>
#include "text_frames.h"
#include <time.h>

// Constants
const int led_pins[] = {10, 9, 8, 7, 6, 5, 4, 3};
const int num_of_leds = 8;
const int size_of_frame = 100;
unsigned long int rpm, maxRPM;
const double PI_2 = M_PI * 2;

// Angles
double angle = 0;
double anglePerMilisecond = 160.0 / 1000; //Angle per second div by 1000
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
    //Serial.print(val);
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
  //Serial.begin(9600);
  pinMode(13, INPUT);
  for (int i = 0; i < num_of_leds; i++)
  {
    pinMode(led_pins[i], OUTPUT);
  }
  TextFrame textFrame;
  char text[] = {'B', 'C', 'S', 'S'};
  frame = textFrame.convertStringToFrame(text);
  size = textFrame.getSize();
  lastUpdateTime = millis();
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
      //Serial.println(sliceIndex);
    }
    // Delay for framerate
    updateAngle();
    // sliceIndex = getSliceIndex(angle, (3 * M_PI) / 2, M_PI / 2);
    sliceIndex = getSliceIndex(angle, PI_2, 0);
    // sensor
    //float a = digitalRead(13);
    //Serial.println(a);
    // Tick speed
    //delay(1);
}
