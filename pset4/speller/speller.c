#include <stdio.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

struct TrieNode
{
    bool word;
    TrieNode *children[];
}