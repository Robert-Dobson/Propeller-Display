
// #include <Arduino.h>
#include <math.h>
#include <time.h>
#include <iostream>
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
    angle += (anglePerSecond*timeDifference) % (2 * M_PI);
    lastUpdateTime = currentTime;
}

void getSlice() {

}