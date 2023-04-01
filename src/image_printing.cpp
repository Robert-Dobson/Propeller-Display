
// #include <Arduino.h>
#include <math.h>
#include <time.h>

using namespace std;

// Characters
unsigned char Alphabet[26][8]=
   {{0,0b01111111,0b11111111,0b11001100,0b11001100,0b11001100,0b11111111,0b01111111},
    {0,0b00111100,0b01111110,0b11011011,0b11011011,0b11011011,0b11111111,0b11111111},
    {0,0b11000011,0b11000011,0b11000011,0b11000011,0b11100111,0b01111110,0b00111100},
    {0,0b01111110,0b10111101,0b11000011,0b11000011,0b11000011,0b11111111,0b11111111},
    {0,0b11011011,0b11011011,0b11011011,0b11011011,0b11011011,0b11111111,0b11111111},
    {0,0b11011000,0b11011000,0b11011000,0b11011000,0b11011000,0b11111111,0b11111111},
    {0b00011111,0b11011111,0b11011000,0b11011011,0b11011011,0b11011011,0b11111111,0b11111111},
    {0,0b11111111,0b11111111,0b00011000,0b00011000,0b00011000,0b11111111,0b11111111},
    {0b11000011,0b11000011,0b11000011,0b11111111,0b11111111,0b11000011,0b11000011,0b11000011},
    {0b11000000,0b11000000,0b11000000,0b11111111,0b11111111,0b11000011,0b11001111,0b11001111},
    {0,0b11000011,0b11100111,0b01111110,0b00111100,0b00011000,0b11111111,0b11111111},
    {0b00000011,0b00000011,0b00000011,0b00000011,0b00000011,0b00000011,0b11111111,0b11111111},
    {0b11111111,0b11111111,0b01100000,0b01110000,0b01110000,0b01100000,0b11111111,0b11111111},
    {0b11111111,0b11111111,0b00011100,0b00111000,0b01110000,0b11100000,0b11111111,0b11111111},
    {0b01111110,0b11111111,0b11000011,0b11000011,0b11000011,0b11000011,0b11111111,0b01111110},
    {0,0b01110000,0b11111000,0b11001100,0b11001100,0b11001100,0b11111111,0b11111111},
    {0b01111110,0b11111111,0b11001111,0b11011111,0b11011011,0b11000011,0b11111111,0b01111110},
    {0b01111001,0b11111011,0b11011111,0b11011110,0b11011100,0b11011000,0b11111111,0b11111111},
    {0b11001110,0b11011111,0b11011011,0b11011011,0b11011011,0b11011011,0b11111011,0b01110011},
    {0b11000000,0b11000000,0b11000000,0b11111111,0b11111111,0b11000000,0b11000000,0b00000000},
    {0b11111110,0b11111111,0b00000011,0b00000011,0b00000011,0b00000011,0b11111111,0b11111110},
    {0b11100000,0b11111100,0b00011110,0b00000011,0b00000011,0b00011110,0b11111100,0b11100000},
    {0b11111110,0b11111111,0b00000011,0b11111111,0b11111111,0b00000011,0b11111111,0b11111110},
    {0b01000010,0b11100111,0b01111110,0b00111100,0b00111100,0b01111110,0b11100111,0b01000010},
    {0b01000000,0b11100000,0b01110000,0b00111111,0b00111111,0b01110000,0b11100000,0b01000000},
    {0b11000011,0b11100011,0b11110011,0b11111011,0b11011111,0b11001111,0b11000111,0b11000011}
    };

// Other constants
int const LEDCount = 8;
bool screen[10][6];
double angle;
double anglePerSecond;
double lastUpdateTime;

void drawSlice(int index) {
    for (int i = 0; i < LEDCount; i++)
    {
        //Serial.println(screen[index][i]);
    }
    
}

int updateAngle() {
    double currentTime = time(0);
    double timeDifference = difftime(currentTime, lastUpdateTime);
    // angle += (anglePerSecond*timeDifference) % 360;
    lastUpdateTime = currentTime;
}

int getSliceIndex(int frame[][LEDCount], double angle) {
    // Calculate proportion through frame using angle then return correct slice of frame
    int width = sizeof(frame)/sizeof(frame[0]);
    return round(angle/(2 * M_PI) * width); 
}

int getCharFrameIndex(char letter){
    int index = letter - 65;
    return index;
}
