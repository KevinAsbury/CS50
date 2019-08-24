// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
} node;

// Represents a trie
node *root;

unsigned int words = 0;

char toLower(char c);
void insert(struct node *t_root, const char *key);
bool isAlpha(char c);
int freeTrie(node *children);

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }

    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        words += 1;
        insert(root, word);
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int len = strlen(word);
    int i = 0;
    struct node *t = root;

    for (int letter = 0; letter < len; letter++)
    {
        if (isAlpha(word[letter]))
        {
            i = toLower(word[letter]) - 'a';
        }
        else
        {
            i = 26;
        }

        if (!t->children[i])
        {
            return false;
        }

        t = t->children[i];
    }

    return (t != NULL && t->is_word);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *t = root;
    return freeTrie(t);
}

struct node *getNode(void)
{
    struct node *t = NULL;
    t = (struct node *)malloc(sizeof(struct node));

    if (t)
    {
        int i;
        t->is_word = false;
        for (i = 0; i < N; i++)
        {
            t->children[i] = NULL;
        }
    }

    return t;
}

void insert(struct node *t_root, const char *key)
{
    int i = 0;
    struct node *t = t_root;

    for (int letter = 0; letter < strlen(key); letter++)
    {
        if (isAlpha(key[letter]))
        {
            i = key[letter] - 'a';
        }
        else
        {
            i = 26;
        }

        if (!t->children[i])
        {
            t->children[i] = getNode();
        }

        t = t->children[i];
    }

    t->is_word = true;
}

char toLower(char c)
{
    if ('A' <= c && c <= 'Z')
    {
        return c + 32;
    }

    return c;
}

bool isAlpha(char c)
{
    if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
    {
        return true;
    }

    return false;
}

int freeTrie(node *children)
{
    if (children == NULL)
    {
        return 0;
    }

    int count = 1;

    for (int i = 0; i < N; i++)
    {
        if (children->children[i] != NULL)
        {
            count += freeTrie(children->children[i]);
        }
    }

    free(children);

    return count;
}