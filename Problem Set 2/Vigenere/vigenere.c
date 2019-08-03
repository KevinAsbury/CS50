#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int message_exit(void);
void print_char(int);
int shift(char c);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        message_exit();
        return 1;
    }

    string key_phrase = argv[1];

    for (int i = 0; i < strlen(key_phrase); i++)
    {
        if (isdigit(key_phrase[i]) || !isalpha(key_phrase[i]))
        {
            message_exit();
            return 1;
        }
    }

    string message = get_string("plaintext: ");

    int c = strlen(key_phrase);
    int key = 0;
    int n = strlen(message);

    printf("ciphertext: ");

    for (int i = 0, j = 0; i < n; i++)
    {
        if (!isupper(message[i]) && !islower(message[i]))
        {
            print_char(message[i]);
            j++;
        }

        key = shift(key_phrase[(i - j) % c]);

        if (isupper(message[i]))
        {
            if (message[i] + key > 'Z')
            {
                print_char((message[i] + key) - 26);
            }
            else
            {
                print_char(message[i] + key);
            }
        }
        else if (islower(message[i]))
        {
            if (message[i] + key > 'z')
            {
                print_char((message[i] + key) - 26);
            }
            else
            {
                print_char(message[i] + key);
            }
        }
    }

    printf("\n");

    return 0;
}

int message_exit(void)
{
    printf("Usage: ./vigenere keyword\n");
    return 1;
}

void print_char(int i)
{
    printf("%c", i);
}

int shift(char c)
{
    int i = (int)toupper(c);
    return i % 65;
}
