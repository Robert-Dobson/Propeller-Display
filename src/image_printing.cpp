
#include <Arduino.h>
#include <math.h>
#include <time.h>

using namespace std;

int const LEDCount = 6;
bool screen[10][6];
double angle;
double anglePerSecond;
double lastUpdateTime;

void drawSlice(int index) {
    for (int i = 0; i < LEDCount; i++)
    {
        Serial.println(screen[index][i]);
    }
    
}

// void updateAngle() {
//     double currentTime = time(0);
//     double timeDifference = difftime(currentTime, lastUpdateTime);
//     angle += (anglePerSecond*timeDifference) % 360;
//     lastUpdateTime = currentTime;
// }

// int getSliceIndex(int frame[][LEDCount], double angle) {
//     // Calculate proportion through frame using angle then return correct slice of frame
//     int width = sizeof(frame)/sizeof(frame[0]);
//     return round(angle/(2 * M_PI) * width); 
// }