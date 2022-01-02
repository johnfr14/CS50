#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // Ask the user for the height of the pyramide must be above 0 and below your 9
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // loop for each raw
    for (int i = height; i > 0; i--)
    {
        // fill the blank depending of the raw
        for (int k = 0; k < i - 1; k++)
        {
            printf(" ");
        }
        // fill the pyramide_side depending of the raw
        for (int j = 0; j < height - (i - 1); j++)
        {
            printf("#");
        }
        printf("  ");
        // fill the pyramide_side depending of the raw
        for (int k = 0; k < height - (i - 1); k++)
        {
            printf("#");
        }
        printf("\n");
    }
}