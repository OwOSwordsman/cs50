// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// prototype
void freeNode(node *n);

// Number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[100];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hashedWord = hash(word);   // hash word

    // loop through every linked node for the table at the hashed index
    // and check if the word matches
    for (node *tmp = table[hashedWord]; tmp != NULL; tmp = tmp -> next) {
        if (!strcasecmp(word, tmp -> word)) return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashVal = 3;    // initial val

    // multiply all the ascii values for each of the letter in the word
    for (int i = 0, l = strlen(word); i < l; i++) {
        char tmp = toupper(word[i]);
        hashVal *= tmp;
    }
    return hashVal % N; // mod value to ensure it is within table index
}

unsigned int dictCt = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // populate table with null nodes
    for (int i = 0; i < N; i++) {
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL) return false;
        tmp -> next = NULL;
        tmp -> word[0] = '\0';
        table[i] = tmp;
    }

    // open dictionary, set to read mode, check for null
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL) return false;

    // read word, hash, insert into table
    char curWord[LENGTH + 1];
    while (fscanf(dict, "%s", curWord) != EOF) {
        dictCt++;   // count dict entries

        // allocate mem for node
        node *n = malloc(sizeof(node));
        if (n == NULL) return false;

        strcpy(n -> word, curWord);
        unsigned int hashOutput = hash(curWord);
        n -> next = table[hashOutput] -> next;
        table[hashOutput] -> next = n;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictCt;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // free nodes at every element of the table
    for (int i = 0; i < N; i++) {
        freeNode(table[i]);
    }
    return true;
}

void freeNode(node *n) {
    // base case
    if (n == NULL) return;

    // free child
    freeNode(n -> next);

    // free self
    free(n);
}
