// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1]; // the data we wish to store in the node
    struct node *next; // defines a pointer to the next node in the linked list
}
node;
node *hashtable[26]; // this is the HEAD

int hash_function(const char *word); // hash function, will return an int 0-25 for our letters of the alphabet
int counter; // this will keep track of how many words we add into our dictionary in load, and gets returned in size
int hashIndex; // this will keep track of our index in our array of linked lists
const int HASHTABLESIZE = 26;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // int srtcasecmp(const char *string1, const char *string2);
    int strCaseCmp; // will be used to store integer from strcasecmp function
    hashIndex = hash_function(word); // gives us the index of the word we need to check. we know it will be in this index, if exists

    node *cursor = hashtable[hashIndex];

    // while loop runs until the cursor points to NULL, which means we made it to the end of our linked list and can move onto the
    // next index of our array of linked lists
    while (cursor != NULL)
    {
        // char *wordCheck = cursor->word;
        strCaseCmp = strcasecmp(word, cursor->word); // compares the word with the first word of our linked list at the hash index
        if (strCaseCmp == 0)
        {
            return true; // return if we found the word in the dictrionary
        }
        else
        {
            cursor = cursor->next; // else we move to the next word in our linked list
        }
    }

    return false; // return false if we didn't find word, word is mispelled
}
// Loads dictionary into memory, returning true if successful else false
// Uses a data structure we have created
bool load(const char *dictionary)
{
    // TODO - LOAD DICTIONARY FILE INTO A HASH TABLE
    char word[LENGTH + 1]; // makes room for any word that will be possibly be entered into dictionary (LENGTH == 45)
    FILE *file = fopen(dictionary, "r"); // opens dictionary file to read

    while (fscanf(file, "%s", word) != EOF) // loops until it reaches end of file
    {

        // create new node called new_node
        node *new_node = malloc(sizeof(node));

        // check for NULL
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // initialize new node
        // copies the new word into the member called word from the struct that new_node points to
        // foo->bar is equivalent to (*foo).bar, i.e. it gets the member called bar from the struct that foo points to.
        // The → operator is a shorthand for "follow the pointer to the struct and access this field within the struct."
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // returns an index to use to place our word. 0-25 for letters of alphabet
        // hashIndex = hash_function(new_node->word));
        // OR
        hashIndex = hash_function(word);

        // insert new node at head
        new_node->next = hashtable[hashIndex]; // hashtable[hashIndex] is the HEAD
        hashtable[hashIndex] = new_node; // set the head to new node

        counter++; // this is keeping track of how many words we are adding to the dictionary
    }

    fclose(file); // closes the dictionary file

    return true;
    // return true if loop is successful
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // for each word in the dictionary text file, store it in the dictionary's data structure
    if (counter)
    {
        return counter;
    }
    else
    {
        return 0;
    }

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // NEED TO FREE ANY MEMORY ALLOCATED IN LOAD IN HERE.
    // USE VALGRIND

    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        node *cursor = hashtable[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

    }

    return true;

}

// hash function to return our index for the array of linked lists
// HASH FUNCTION TAKEN FROM https://study.cs50.net/hashtables
int hash_function(const char *key)
{
    int hash = (tolower(key[0]) - 'A');
    return hash % HASHTABLESIZE;
}