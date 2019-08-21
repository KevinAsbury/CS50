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
    
    // Create the character buffers
    char left[height + 1];
    char right[height + 1];
    
    // Loop through each line
    for (int i = 0; i < height; i++) 
    {
        // Loop through each character on the line
        for (int j = 0; j < height; j++) 
        {
            // Insert space or # on left
            if (j < height - i - 1) 
            {
                left[j] = ' ';
            }
            else
            {
                left[j] = '#';
            }
            
            // Insert # or nothing on right
            if (j < i + 1)
            {
                right[j] = '#';
            }
        }
        
        // Terminate the two char buffers
        left[height] = '\0';
        right[height] = '\0';
        
        // Display the combined results
        printf("%s  %s\n", left, right);
    }
}
