
// #include <Arduino.h>
#include <math.h>
#include <time.h>

using namespace std;

bool screen[10][6];
double angle;
double anglePerSecond;
double lastUpdateTime;

void drawSlice(int index) {
    int LEDCount = 6;
    for (int i = 0; i < LEDCount; i++)
    {
        cout << screen[index][i];
    }
    
}

int updateAngle() {
    double currentTime = time(0);
    double timeDifference = difftime(currentTime, lastUpdateTime);
    angle += (anglePerSecond*timeDifference) % 360;
    lastUpdateTime = currentTime;
}

int getSliceIndex(int frame[][6], double angle) {
    // Calculate proportion through frame using angle then return correct slice of frame
    int length = sizeof(frame)/sizeof(int[6]);
    return round(angle/(2 * M_PI) * length); 
}