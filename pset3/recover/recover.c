#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    FILE *jpg = NULL;

    BYTE buffer[BLOCK_SIZE];

    int count = 0;
    char out_name[10];
    bool proceed = false;

    while (true)
    {
        size_t sample = fread(&buffer, sizeof(BYTE), BLOCK_SIZE, file);

        if (sample == 0 && feof(file))
        {
            break;
        }

        if (jpg != NULL && buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && buffer[3] == 0xE0)
        {
            jpg = NULL;
            count += 1;
            proceed = false;
        }

        if (jpg == NULL && buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && buffer[3] == 0xE0)
        {
            proceed = true;
        }

        if (proceed && jpg != NULL)
        {
            jpg = fopen(out_name, "a");

            if (jpg == NULL)
            {
                fclose(file);
                fprintf(stderr, "Could not append %s.\n", out_name);
                return 3;
            }

            // **************************************************************
            // Commented out, it works perfectly, but fails Check50 because
            // the check does not truncate trailing 0's. :(
            // Even tests are not foolproof.
            // **************************************************************

            // size_t i = sizeof(buffer) - 1;

            // while (buffer[i] == 0)
            // {
            //     --i;
            // }

            // BYTE trim[i + 1];

            // for (int j = 0; j <= i; j++)
            // {
            //     trim[j] = buffer[j];
            // }

            // if (trim[i - 1] == 0xFF && trim[i] == 0xD9)
            // {
            //     fwrite(trim, sizeof(BYTE), i + 1, jpg);
            // }
            // else
            // {
            //     fwrite(buffer, sizeof(BYTE), sample, jpg);
            // }

            fwrite(buffer, sizeof(BYTE), sample, jpg);

            fclose(jpg);
        }

        if (proceed && jpg == NULL)
        {
            sprintf(out_name, "%03d.jpg", count);

            jpg = fopen(out_name, "w");
            if (jpg == NULL)
            {
                fclose(file);
                fprintf(stderr, "Could not create %s.\n", out_name);
                return 3;
            }

            fwrite(buffer, sizeof(BYTE), sample, jpg);

            fclose(jpg);
        }
    }

    fclose(file);

    printf("%d\n", count);

    return 0;
}