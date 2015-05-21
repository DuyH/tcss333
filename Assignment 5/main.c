/*
 * main.c
 *
 *  Created on: May 18, 2015
 *      Author: duy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_WORD_LENGTH 50
#define ASCII_SHIFT 32

void testList(List*); // del when done
void readText(char*, List*);

int main(void) {

    List *list = malloc(sizeof(List));

    //readText("RedBadge.txt", list);

    testList(list);

    return 1;
}

void readText(char* fileName, List *list) {

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
        printf("%d) %s\n", j++, word);
        addWord(list, word, 1);
        // The problem: word is being wiped

    }
    printList(list);
    printf("%d", length(list));
}

void testList(List* list) {

    addWord(list, "A", 1);
    addWord(list, "B", 1);
    addWord(list, "C", 1);
    addWord(list, "D", 1);
    addWord(list, "E", 1);
    addWord(list, "F", 1);
    addWord(list, "G", 1);
    addWord(list, "H", 1);
    addWord(list, "A", 1);
    addWord(list, "B", 1);
    addWord(list, "C", 1);
    addWord(list, "D", 1);
    addWord(list, "E", 1);
    addWord(list, "F", 1);
    addWord(list, "G", 1);
    addWord(list, "H", 1);

    printList(list);
    printf("Length of list is %d", length(list));

}
