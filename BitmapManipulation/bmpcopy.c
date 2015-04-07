/*
 * main.c
 *
 *  Created on: Apr 6, 2015
 *      Author: duy
 */

#include <stdio.h>

int main(void) {

	FILE *infile = fopen("test1.bmp", "rb"); // rb = readbinary
	FILE *outfile = fopen("copytest1.bmp", "wb"); // wb  = write binary

	char arr[115254]; // Size of our image file (in bytes)

	fread(arr, 1, 115254, infile); // read in the image file
	fwrite(arr, sizeof(char), 115254, outfile); // write out the image file
	// sizeof(char) tells you the size (bytes) of the type given

	fclose(infile);
	fclose(outfile);

	return 0;
}

