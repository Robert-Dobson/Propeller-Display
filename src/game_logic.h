#include <Arduino.h>
#pragma once

class GameLogic
{
public:
    // Constants
    int width = 50;
    int height = 8;

    // Obstacles
    int obstacles[5];

    // Stats
    int xPos = 0;
    int yPos = 2;
    int jumpTimer = 0;
    bool jumping = false;

    // Game
    bool gameRunning = true;

    void gameStartup();
    void gameTick();
    unsigned char *generateFrame();
};