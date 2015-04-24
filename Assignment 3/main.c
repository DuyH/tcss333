/*
 * main.c
 *
 *  Created on: Mar 29, 2015
 *      Author: Duy
 */

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_NAMES 366
#define MAX_NUM_YEARS 10
#define MAX_TOP_NAMES 100
#define LINE_BUFFER 20

void readAllFiles();
void readFile();
//void processOneNameRank();
//void sortArrays();
//void createOutputFile();

int main(void) {
    printf("This is main!\n");

    readAllFiles();
    return 0;
}

void readAllFiles() {

    char totalNames[MAX_NAMES][MAX_NAME_LENGTH];
    int totalRanks[MAX_NAMES][MAX_NUM_YEARS];

    int year = 0;
    readFile("names/yob1920.txt", &totalNames, &totalRanks, year++);
    //readFile("names/yob1930.txt", &totalNames, &totalRanks, year++);
    //readFile("names/yob1940.txt", &totalNames, &totalRanks, year++);
    //readFile("names/yob1950.txt", &totalNames, &totalRanks, year++);
    //readFile("names/yob1960.txt", &totalNames, &totalRanks, year++);
    //readFile("names/yob1970.txt", &totalNames, &totalRanks, year++);
    //readFile("names/yob1980.txt", &totalNames, &totalRanks, year++);
    // readFile("names/yob1990.txt", &totalNames, &totalRanks, year++);
    //readFile("names/yob2000.txt", &totalNames, &totalRanks, year++);
    // readFile("names/yob2010.txt", &totalNames, &totalRanks, year++);

}

void readFile(char *fileName, char (*totalNames)[MAX_NAME_LENGTH],
        int (*totalRanks)[MAX_NUM_YEARS], int year) {

// Load one name file:
    FILE *inputFile = fopen(fileName, "r");
    char name[LINE_BUFFER];

    // Grab the first 100 (MAX_TOP_NAMES) names with i+1 being the rank
    int i;
    for (i = 0; i < MAX_TOP_NAMES; i++) {

        // Grab one line from the file
        fgets(name, LINE_BUFFER, inputFile);

        // Find the name by replacing the first ',' with '\0'
        int j = 0;
        while (name[j] != ',')
            j++;
        name[j] = '\0';

        processOneNameRank(name, (i + 1), year, totalNames, totalRanks);

    }

    fclose(inputFile);

}

void processOneNameRank(char *name, int rank, int year,
        char (*totalNames)[MAX_NAMES], int (*totalRanks)[MAX_NUM_YEARS]) {
    int i;
    for (i = 0; i < 50; i++) {

        if (strcmp(name, totalNames[i]) == 0) {
            totalRanks[i][year] = rank;
            printf("%s ", totalNames[i]);
            break;
        } else if (totalNames[i][0] == '\0') {
            strcpy(totalNames[i], name);
            totalRanks[i][year] = rank;
            printf("%s ", totalNames[i]);
            break;
        }

    }

}
