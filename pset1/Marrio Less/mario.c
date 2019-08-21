#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Declare the variables
    int height;
     
    // Only accept 1-8 as viable answers
    do 
    {
        height = get_int("Height: ");
    } 
    while (height < 1 || height > 8);
    
    // Loop through each line
    for (int i = 0; i < height; i++)
    {
        // Print each space character in the line
        for (int j = 0; j <= height - i; j++)
        {
            printf(" ");
        }
        
        // Print each # character in the line
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        
        // Advance to the next line
        printf("\n");
    }
}
