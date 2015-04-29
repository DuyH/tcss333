/*
 * nestedStructsFromFile.c
 *
 *  Created on: Oct 10, 2014
 *      Author: jhmayer
 */

#include <stdio.h>
#include <string.h>   // you'll need this once you start using strcpy, strcmp, etc.

struct weather_tag {
	char city[20];
	int temp;
};

typedef struct weather_tag Weather;



int main(void) {
    FILE *infile;
    int i;

    Weather arr[10];
    Weather w;
    int arrCount = 0;

    char inCity[20];
    int inTemp;

    setvbuf(stdout, NULL, _IONBF, 0);
    infile = fopen("cities.txt", "r");

    // How do you know if the file open was successful?
    // Here's how you can check.
    if (infile == NULL) {
    	printf("File did not open.");
    	return 1;
    }

    // It's easy to read a file to the end.
    // fscanf returns a value that indicates whether
    // it ran off the end of the file.
    while (fscanf(infile, "%s %d", inCity, &inTemp) != EOF) {

    	w.temp = inTemp;
    	strcpy(w.city, inCity);

        // put into array
        arr[arrCount] = w;
        arrCount++;
    }

    // print out all the data from the array
    for (i = 0; i < arrCount; i++) {
        printf("%s %d\n", arr[i].city, arr[i].temp);
    }

    return 0;

}
