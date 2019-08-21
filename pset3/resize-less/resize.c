// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy <Multiplier> <infile> <outfile>\n");
        return 1;
    }

    // remember filenames
    int multiplier = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Rewind
    fseek(inptr, 0, SEEK_SET);

    // Make a duplicate for the output
    // Doing this to avoid shallow copy issues
    BITMAPFILEHEADER new_bf;
    fread(&new_bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Rewind
    fseek(inptr, 14, SEEK_SET);

    // Make a duplicate for the output
    // Doing this to avoid shallow copy issues
    BITMAPINFOHEADER new_bi;
    fread(&new_bi, sizeof(BITMAPINFOHEADER), 1, inptr);


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    new_bi.biWidth = bi.biWidth * multiplier;
    new_bi.biHeight = bi.biHeight * multiplier;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int new_padding = (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Calculate the new file size
    new_bi.biSizeImage = ((new_bi.biWidth * 3) + new_padding) * abs(new_bi.biHeight);
    new_bf.bfSize = new_bi.biSizeImage + 54;
    // printf("%d\n", new_bf.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Multiply each line
        for (int m = 0; m < multiplier; m++)
        {
            // Position Counter
            int seek = 0;

            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int k = 0; k < multiplier; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

                // Set the return position
                seek -= sizeof(RGBTRIPLE);
            }

            // Adjust for any padding
            seek -= padding;

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int l = 0; l < new_padding; l++)
            {
                fputc(0x00, outptr);
            }

            // Rewind back for muliplier
            if ((m < multiplier - 1))
            {
              fseek(inptr, seek, SEEK_CUR);
            }

        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
