# Questions

## What's `stdint.h`?

A header file that defines fixed width integers. 

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Which is useful on projects where you need to know the width of the types you are using.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE: 2^3 bits (or 8 bits) which is 1 byte
WORD: 2^4 bits (or 16-bits) which is 2 bytes
DWORD: 2^5 bits (or 32 bits) which is 4 bytes
LONG: 2^5 bits (or 32 bits) which is 4 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x42 0x4D

## What's the difference between `bfSize` and `biSize`?

bfSize contains the size of the entire bmp file in bytes where as biSize is just the size of the BITMAPINFOHEADER in bytes.

## What does it mean if `biHeight` is negative?

That the bitmap is stored from the top to bottom if this is a windows bitmap.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

The file may not exisit or there may not be the proper permissions to read the file.

## Why is the third argument to `fread` always `1` in our code?

Because we are reading 1 byte at a time from the filestream.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

0

## What does `fseek` do?

Finds a specific spot in the filestream and goes to it.

## What is `SEEK_CUR`?

It provides the current position of the pointer in the filestream.
