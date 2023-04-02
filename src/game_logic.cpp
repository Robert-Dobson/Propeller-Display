#include <Arduino.h>
#include "game_logic.h"

void GameLogic::gameStartup() {
    for (int i = 0; i < sizeof(obstacles); i++)
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
    for (int i = 0; i < sizeof(obstacles); i++)
    {
        // If player has just moved past an obstacle
        if ((obstacles[i] + 3) % width == xPos)
        {
            //Despawn obstacle
            obstacles[i] = -1;
        }
    }

    // Obstacle Collision
    for (int i = 0; i < sizeof(obstacles); i++)
    {
        if (obstacles[i] > (xPos - 1) % width && obstacles[i] < (xPos + 1) % width)
        {
            gameRunning = false;
        }
    }

    // Obstacle Generation
    for (int i = 0; i < sizeof(obstacles); i++)
    {
        //If there's an unspawned in obstacle
        if (obstacles[i]==-1)
        {
            int spawnPos = (xPos - 5) % width;
            if (spawnPos < 0)
            {
                spawnPos + width;
            }
            for (int j = 0; j < sizeof(obstacles); j++)
            {
                if (j != i)
                {
                    //If there's no obstacles nearby
                    if (obstacles[j]-spawnPos < 6 && obstacles[j]-spawnPos > -6)
                    {
                        //Attempt to spawn in, 30% chance
                        int random;
                        //random = millis() % 10 < 4;
                        obstacles[i] = spawnPos;
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
    for (int i = 0; i < sizeof(obstacles); i++)
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
    //Convert to char array
    unsigned char output[width];
    for (int i = 0; i < width; i++)
    {
        char byte = 0;
        for (int j = 0; j < height; j++)
        {
            if (Frame[i][j])
            {
                byte << 1;
                byte++;
            }
            
        }
        output[width] = byte;
    }
    return output;
}