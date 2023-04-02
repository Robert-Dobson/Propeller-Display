#include <Arduino.h>
#include "game_logic.h"

void GameLogic::gameStartup()
{
    int length = sizeof(obstacles) / sizeof(int);
    for (int i = 0; i < length; i++)
    {
        obstacles[i] = -1;
    }
    xPos = 0;
    yPos = 1;
    jumpTimer = 0;
    jumping = false;
}

void GameLogic::gameTick()
{
    // Player xPos update
    xPos++;
    if (xPos > width)
    {
        xPos = 0;
    }

    // Player jump update
    if (jumpTimer > 1)
    {
        jumpTimer--;
    }
    else if (jumpTimer == 1)
    {
        jumpTimer = 0;
        yPos = 1;
    }
    else if (jumping)
    {
        jumpTimer = 5;
        yPos = 3;
    }

    // Obstacle Despawn
    int length = sizeof(obstacles) / sizeof(int);
    for (int i = 0; i < length; i++)
    {
        // If player has just moved past an obstacle
        if ((obstacles[i] + 3) % width == xPos)
        {
            // Despawn obstacle
            obstacles[i] = -1;
        }
    }

    // Obstacle Collision
    for (int i = 0; i < length; i++)
    {
        if (obstacles[i] > (xPos - 1) % width && obstacles[i] < (xPos + 1) % width)
        {
            gameRunning = false;
        }
    }

    // Obstacle Generation
    for (int i = 0; i < length; i++)
    {
        // If there's an unspawned in obstacle
        if (obstacles[i] == -1)
        {
            int spawnPos = (xPos - 5) % width;
            if (spawnPos < 0)
            {
                spawnPos += width;
            }
            for (int j = 0; j < length; j++)
            {
                if (j != i)
                {
                    // If there's no obstacles nearby
                    if (obstacles[j] - spawnPos < 6 && obstacles[j] - spawnPos > -6)
                    {
                        // Attempt to spawn in, 30% chance
                        bool random;
                        random = millis() % 10 < 4;
                        if (random)
                        {
                            obstacles[i] = spawnPos;
                        }
                    }
                }
            }
        }
    }
}

unsigned char *GameLogic::generateFrame()
{
    bool Frame[width][height] = {0};
    // Player draw
    int playerWidth = 2;
    int playerHeight = 2;
    for (int i = xPos; i < playerWidth; i = (i + 1) % width)
    {
        for (int j = yPos; j < playerHeight; j = (j + 1) % height)
        {
            Frame[i][j] = true;
        }
    }
    // Ground draw
    for (int i = 0; i < width; i++)
    {
        Frame[i][0] = true;
    }
    // Obstacle draw
    int obstacleWidth = 2;
    int obstacleHeight = 2;
    int length = sizeof(obstacles) / sizeof(int);
    for (int i = 0; i < length; i++)
    {
        if (obstacles[i] >= 0)
        {
            for (int j = obstacles[i]; j < obstacleWidth; j = (j + 1) % width)
            {
                for (int k = 1; k < obstacleHeight; k = (k + 1) % height)
                {
                    Frame[j][k] = true;
                }
            }
        }
    }
    // Convert to char array
    unsigned char *output = (unsigned char *)malloc((width * 8) * sizeof(unsigned char));
    for (int i = 0; i < width; i++)
    {
        char byte = 0;
        for (int j = 0; j < height; j++)
        {
            if (Frame[i][j])
            {
                byte = byte << 1;
                byte++;
            }
        }
        output[width] = byte;
    }
    return output;
}