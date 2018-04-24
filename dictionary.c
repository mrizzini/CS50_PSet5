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

// hash function, will return an int 0-25 for our letters of the alphabet
int hash_function(const char *word);
int counter;
int hashIndex;



// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // int srtcasecmp(const char *string1, const char *string2);
    // printf("%s", word);
    int checkWord;
    // int hashIndex = 0;
    // int hashIndex;
    hashIndex = hash_function(word);

    // return false;

    node *cursor = hashtable[hashIndex];


    while (cursor != NULL)
    {
        char *wordCheck = cursor->word;
        checkWord = strcasecmp(word, wordCheck);
        if (checkWord == 0)
        {
            return true;
        }
        else
        {
            // hashIndex++;
            cursor = cursor->next;
        }
    }

    return false;
}
// Loads dictionary into memory, returning true if successful else false
// Uses a data structure we have created
bool load(const char *dictionary)
{
    // TODO

    // int hashIndex;
    char word[LENGTH + 1];

    FILE *file = fopen(dictionary, "r"); // opens dictionary file to read

    while (fscanf(file, "%s", word) != EOF)
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
        new_node->next = hashtable[hashIndex];
        hashtable[hashIndex] = new_node;
        // new_node->next = hashtable[hashIndex];
        //  new_node->next = NULL; // do we do this instead of the above?

// new_node->word = word

        // new_node-> = head;
        // head = new_node;
        counter++;
    }

    fclose(file);

    return true;
    // return true if successful
    // return false;
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

    for (int i = 0; i < 26; i++)
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


int hash_function(const char* key)
{
    int hash = (tolower(key[0]) - 'A');
    return hash % 26;
}