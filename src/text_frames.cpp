#include <Arduino.h>
#include "text_frames.h"

int TextFrame::getCharFrameIndex(char letter)
{
    int index = letter - 65;
    return index;
}

unsigned char *TextFrame::convertStringToFrame(char *text)
{
    unsigned char *frame = (unsigned char *)malloc((sizeof(*text) * 8 + spaceBetweenLetters) * sizeof(unsigned char));
    int index = 0; // Keeping track of position in frame

    if (frame != NULL)
    {
        // Iterate through each letter of string
        int length = sizeof(text) / sizeof(char);
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
            else if (65 < letter < 90)
            {
                // Otherwise copy in slices from alphabet
                for (int i = 0; i < 8; i++)
                {
                    frame[index] = Alphabet[getCharFrameIndex(letter)][7-i];
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

        size = index + 1;
    }
    return frame;
}

int TextFrame::getSize()
{
    return size;
}

