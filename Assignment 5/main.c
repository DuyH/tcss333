/*
 * main.c
 *
 *  Created on: May 18, 2015
 *      Author: duy
 */

#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 30
#define A 65
#define Z 90
#define ASCII_SHIFT 32

int main(void) {

    readText("RedBadge.txt");

    return 1;
}

void readText(char* fileName) {

    // Create FILE from text file
    FILE *inputFile = fopen(fileName, "r");

    //Process each line until end-of-file reached
    while (!feof(inputFile)) {

        // Read in a word.
        char word[MAX_WORD_LENGTH];
        fscanf(inputFile, "%s", word);

        // Convert each uppercase to lowercase.
        int i = 0;
        for (i = 0; i < strlen(word); i++) {
            // If the char is within the Uppercase range...
            if (word[i] >= A && word[i] <= Z)
                // Convert to lower case, using ASCII shift
                word[i] = word[i] + ASCII_SHIFT;
        }

        // Only allow legal chars (alphabetic, -, ')
        for (i = 0; i < strlen(word); i++) {
            if (!((word[i] >= 'a' && word[i] <= 'z') || word[i] == 39
                    || word[i] == 45)) {
                word[i] = '\0';
            }
        }

        // Now put the word into a node.

        printf("%s", word);

    }
}

