/*
 * main.c
 *
 *  Created on: Mar 29, 2015
 *      Author: Duy
 */

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_NAMES 366 // Number retrieved from class consensus on Catalyst
#define MAX_NUM_YEARS 10
#define MAX_TOP_NAMES 100

//void readAllFiles();
//void readFile();
//void processOneNameRank(char *name, int rank, int year,
//        char (*totalNames)[MAX_NAME_LENGTH], int (*totalRanks)[MAX_NUM_YEARS]);
//void sortArrays();
//void createOutputFile();

int main(void) {

    // 2D array for names
    char totalNames[MAX_NAMES][20] = { '\0' }; // Initialize or else I get junk!

    // 2D array for rank x years: 1910-2010. Parallel to names array.
    int totalRanks[MAX_NAMES][MAX_NUM_YEARS] = { 0 }; // Initialize or else I get junk!

    readAllFiles(totalNames, totalRanks);
    sortArrays(totalNames, totalRanks);

    createOutputFile(totalNames, totalRanks);

    return 0;
}

// Read all [10] name files and process names into
void readAllFiles(char (*totalNames)[MAX_NAME_LENGTH],
        int (*totalRanks)[MAX_NUM_YEARS]) {

    int year = 0, i;
    for (i = 0; i < MAX_NUM_YEARS; i++) {

        // Create String for file name:
        char fileName[18];
        sprintf(fileName, "names/yob%d.txt", 1920 + 10 * i);

        // Read and populate names & ranks array of one file:
        readFile(fileName, totalNames, totalRanks, year++);
    }

}

// Reads one file, one line at a time, extracting name+rank pairs.
void readFile(char *fileName, char (*totalNames)[MAX_NAME_LENGTH],
        int (*totalRanks)[MAX_NUM_YEARS], int year) {

    // Load one name file:
    FILE *inputFile = fopen(fileName, "r");
    char name[MAX_NAME_LENGTH];

    char *namesPtr = &totalNames[0][0];
    int *ranksPtr = &totalRanks[0][0];

    // Grab the first 100 (MAX_TOP_NAMES) names with i+1 being the rank
    int i;
    for (i = 0; i < MAX_TOP_NAMES; i++) {

        // Grab one line from the file
        fgets(name, MAX_NAME_LENGTH, inputFile);

        // Replace first instance of ',' with '\0' for easy String extraction:
        int j = 0;
        while (name[j] != ',') {
            j++;
        }
        name[j] = '\0';

        // Put the name + rank pair into arrays:
        processOneNameRank(name, (i + 1), year, namesPtr, ranksPtr);

    }

    fclose(inputFile);

}

// Takes one line of the file and extracts the name and rank. Places into arrays.
void processOneNameRank(char *name, int rank, int year,
        char (*totalNames)[MAX_NAME_LENGTH], int (*totalRanks)[MAX_NUM_YEARS]) {

    int i;
    char *namePtr = &totalNames[0][0];

    // Find a place in the array to put name+rank pair:
    for (i = 0; i < MAX_NAMES; i++) {

        // If name already present, just add the rank:
        if (strcmp(name, namePtr + 20 * i) == 0) {
            totalRanks[i][year] = rank;
            break;

            // If name not in list, plus in name+rank pair at end:
        } else if (totalNames[i][0] == '\0') { // equiv: *(namePtr + 20 * i)=='\0'
            strcpy(totalNames[i], name); // equiv: namePtr + 20 * i
            totalRanks[i][year] = rank;
            break;
        }
    }
}

// Alphabetize array by bubble sorting
void sortArrays(char (*totalNames)[MAX_NAME_LENGTH],
        int (*totalRanks)[MAX_NUM_YEARS]) {

    int i, j, k;

    // Good ol' bubble sort - alphabetize edition:
    for (i = 0; i < MAX_NAMES; i++) {

        // Bubble up one name:
        for (j = 0; j < MAX_NAMES - 1; j++) {

            // Compare neighboring names and swap if out of order:
            if (strcmp(totalNames[j], totalNames[j + 1]) > 0) {

                // Create a temp for name and swap:
                char temp[strlen(totalNames[j] + 1)];
                strcpy(temp, totalNames[j]);
                strcpy(totalNames[j], totalNames[j + 1]);
                strcpy(totalNames[j + 1], temp);

                // Now also swap ALL years' ranks to new position:
                for (k = 0; k < MAX_NUM_YEARS; k++) {
                    int tempRank;
                    tempRank = totalRanks[j][k];
                    totalRanks[j][k] = totalRanks[j + 1][k];
                    totalRanks[j + 1][k] = tempRank;
                }
            }
        }
    }
}

void createOutputFile(char (*totalNames)[MAX_NAME_LENGTH],
        int (*totalRanks)[MAX_NUM_YEARS]) {

    FILE *csvOutFile = fopen("summary.csv", "w");

    // Write to file the column headings:
    char colHeadings[] = {
            "Name,1920,1930,1940,1950,1960,1970,1980,1990,2000,2010,\n" };
    fwrite(colHeadings, 1, sizeof(colHeadings), csvOutFile);

    // Write name and rankings:
    int i;
    for (i = 0; i < MAX_NAMES; i++) {
        printf("NAME: %s ", totalNames[i]);

        //fwrite(totalNames[i], 1, strlen(totalNames[i]) + 1, csvOutFile);
        //fwrite(",", 1, sizeof(char), csvOutFile);

        int j;
        for (j = 0; j < MAX_NUM_YEARS; j++) {
            printf("%d,", totalRanks[i][j]);
            //putc(',', csvOutFile);
        }
        printf("\n");
        //putc('\n', csvOutFile);

    }
    fclose(csvOutFile);
}
