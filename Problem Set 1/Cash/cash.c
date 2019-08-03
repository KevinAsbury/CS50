#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(int argc, string argv[])
{
    // Declare the variables
    float change;
    int coins = 0;
    
    // Only accept non negative values
    do 
    {
        change = get_float("Change Owed: ");
    } 
    while (change < 0.01f);
    
    int remainder = round(change * 100);;
    
    if (remainder >= 25)
    {
        coins += (remainder - (remainder % 25)) / 25;
        remainder = remainder % 25;
    }
    
    if (remainder >= 10)
    {
        coins += (remainder - (remainder % 10)) / 10;
        remainder = remainder % 10;
    }
    
    if (remainder >= 5)
    {
        coins += (remainder - (remainder % 5)) / 5;
        remainder = remainder % 5;
    }
    
    if (remainder > 0)
    {
        coins += (remainder - (remainder % 1)) / 1;
    }
            
    printf("%d\n", coins);
}
