#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Convert the first argument, which is a string
    // to an integer
    // atoi will return 0 if the string
    // doesn't convert to an integer
    int k = 0;
     
    // Avoid a segmentation fault when user enters no arguments
    if (argc > 1)
    {
        k = atoi(argv[1]);
    }
    else
    {
        return 1;
    }

    // Provide instructions for non-integer input
    if (k < 1)
    {
        printf("Usage: ./caesar key\n");
        return 0;
    }
    
    if (k > 25)
    {
        k = k % 26;
    }

    // Create an empty message buffer
    char message[100];

    // Ask user for input
    printf("plaintext: ");
    scanf("%[^\n]s", message);

    // Find the pivit point where the next
    // letter should circle back to 'A' or 'a'
    // I love that you can do math with chars in C
    int pivotCaps = 'Z' - k;
    int pivotLower = 'z' - k;

    // Removed this n assignment due to it counting
    // whitespace in the message buffer
    // Still a nice what get buffer length
    //  size_t n = sizeof(message) / sizeof(message[0]);

    // Get the length of non-white space in message buffer
    int n = strlen(message);

    // Create a buffer to store the encrypted message
    char secret[n];

    // Loop through each character in the message
    for (int i = 0; i <= n - 1; i++)
    {
        // First copy the char to the secret
        // This will overwrite letters below and
        // leave spaces, punctuation, and special
        // characters alone
        secret[i] = message[i];

        // If the char is a capital then encrypt it
        // and overwrite the char in secret
        if ('A' <= message[i] && message[i] <= 'Z')
        {
            // Same trick as above first shift the letter
            // and write it to the secret
            secret[i] = message[i] + k;

            // If the letter is past the pivot, use a different
            // algorith and overwrite the char in secret
            if (message[i] > pivotCaps)
            {
                // This algorigth will shift letters past the pivot point
                // back to the beginning of the alphabet
                secret[i] = message[i] - ((pivotCaps + 1) - 'A');
            }
        }

        // If the char is a lower then encrypt it
        // and overwrite the char in secret
        if ('a' <= message[i] && message[i] <= 'z')
        {
            // Same trick as above first shift the letter
            // and write it to the secret
            secret[i] = message[i] + k;

            if (message[i] > pivotLower)
            {
                // This algorigth will shift letters past the pivot point
                // back to the beginning of the alphabet
                secret[i] = message[i] - ((pivotLower + 1) - 'a');
            }
        }
    }

    // Print the encrypted result
    printf("ciphertext: %s\n", secret);

    return 0;
}
