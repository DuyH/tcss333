/*
 * main.c
 *
 *  Created on: May 18, 2015
 *      Author: Duy Huynh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_WORD_LENGTH 20
#define ASCII_SHIFT 32
#define PRINT_AMOUNT 50

void readText(char*, List*, int);
void printInOrder(List*);

// Main application, reads in two text files, sorts and prints
int main(void) {

    List *list = malloc(sizeof(List));

    readText("RedBadge.txt", list, 1);
    readText("LittleRegiment.txt", list, 2);
    sortDescending(list);
    printInOrder(list);

    return 1;
}

// Read in a text file, adding words and count to a list
void readText(char* fileName, List *list, int textCount) {

    // Create FILE from text file
    FILE *inputFile = fopen(fileName, "r");

    int j = 0;
    //Process each line until end-of-file reached
    while (!feof(inputFile)) {

        // Read in a word.
        char *word = malloc(MAX_WORD_LENGTH);
        fscanf(inputFile, "%s", word);

        // Convert each uppercase to lowercase.
        int i = 0;
        for (i = 0; i < strlen(word); i++) {
            // If the char is within the Uppercase range...
            if (word[i] >= 'A' && word[i] <= 'Z')
                // Convert to lower case, using ASCII shift
                word[i] = word[i] + ASCII_SHIFT;
        }

        // Only allow legal chars (alphabetic, -, ')
        for (i = 0; i < strlen(word); i++) {
            if (!((word[i] >= 'a' && word[i] <= 'z') || word[i] == '-'
                    || word[i] == '\'')) {
                word[i] = '\0';
            }

        }

        // Now put the word into a node.
        if (word[0] == '\0') { // Skip the "null" word
            continue;
        } else {
            addWord(list, word, textCount);

        }

    }
}

void printInOrder(List * list) {

    Node *currNode = list->head;

    // Print column headers
    printf("    %-9s%-15s%-21s%10s\n", "Word", "RedBadge.txt", "LittleRegiment.txt",
            "Difference");

    int i = 1;
    for (i = 1; i <= PRINT_AMOUNT; i++) {
        printf("%.2d) %-10s %10d %20d %12d\n", i, currNode->word, currNode->count1,
                currNode->count2, currNode->diff);
        currNode = currNode->next;
    }
}

