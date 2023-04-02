#include <Arduino.h>
#include "text_frames.h"

int TextFrame::getCharFrameIndex(char letter)
{
    int index = letter - 65;
    return index;
}

unsigned char *TextFrame::convertStringToFrame(char *text)
{
    int Tindex = 0;
    while (text[Tindex] != '\0'){
        Tindex++;
    }
    int length = Tindex + 1;

    unsigned char *frame = (unsigned char *)malloc((length * 8 + spaceBetweenLetters));
    int index = 0; // Keeping track of position in frame

    if (frame != NULL)
    {
        // Iterate through each letter of string
        
        for (int i = 0; i < length; i++)
        {

            char letter = text[i];
            if (letter == ' ')
            {
                // If string is space, just leave blank space in frame
                for (int i = 0; i < spaceSize; i++)
                {
                    frame[index] = 0;
                    index++;
                }
            }
            else if (letter <= 90 && letter >= 65)
            {
                // Otherwise copy in slices from alphabet
                for (int i = 0; i < 8; i++)
                {
                    frame[index] = Alphabet[getCharFrameIndex(letter)][i];
                    index++;
                }
            }

            // Add space between letters
            for (int i = 0; i < spaceBetweenLetters; i++)
            {
                frame[index] = 0;
                index++;
            }
        }

        size = index;
    }
    return frame;
}

int TextFrame::getSize()
{
    return size;
}

