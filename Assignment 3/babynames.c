/*
 * babynames.c
 *
 *  Created on: Apr 20, 2015
 *      Author: duy huynh
 */

#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER 100
#define MAX_NAMES 100
#define MAX_TOTAL_NAMES 1000

void readAll();
void readFile();
void processNameRank();
void alphabetize();
void outputFile();

int main(void) {
    processNameRank();
    readAll();
}

void readAll() {

    // Make array of File pointers
    FILE *fileName[10];
    char allFile[] = "yob";

    int i;
    int year = 1910;
    char buffer[4];
    for (i = 0; i < 10; i++) {
        year += i * 10;
        sprintf(buffer, "%d", year);
        printf(buffer);
        strcat(allFile, "1020");
        strcat(allFile, "\.txt");
    }
    printf("%s", allFile);

}

void processNameRank() {

//fgets reads a string from file
//fgets returns null if EOF reached!
//fgets returns pointer to 1st character of string just read
// &nameArray[0] = nameArray = char pointer to nameArray

// Obtain a file to read from:
    FILE *nameFile = fopen("yob1920.txt", "r");

// Grab a line from the file
    char line[LINE_BUFFER]; // Holds a single line
    fgets(line, LINE_BUFFER, nameFile);
    printf("%s", line);

// Declare a char[] and ptr for a name:
    char name[LINE_BUFFER];
    char *namePtr = name;

// Declare a char[] and ptr for the rank:
    char rank[100];
    char *rankPtr = rank;

// Read name into array until ","
    int i;
    while (line[i] != ',') {
        *namePtr++ = line[i++];
    }
// Skip over to the rank
    i += 3; // Skips ",F,"

// Read rank into its array until End of Line
    while (line[i] != 0) {
        *rankPtr++ = line[i++];
    }

// Print it out to see what I got
    printf("%s ", name);
    printf("%s", rank);

//At this point, I have a NAME and a RANK
// Now I need to search the namesArray for the name and insert it, plus its rank

}
