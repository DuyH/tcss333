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

	char header1[34]; // bmp file header (before the file size)
	int sizeOfFile;
	char header2[16]; // bytes after the file size piece

	char pixels[160][240 * 3]; //[rows][cols]
	// 240*3 bc 3 is #bytes per pixel

	fread(header1, 1, 34, infile);
	fread(&sizeOfFile, sizeof(int), 1, infile);
	fread(header2, 1, 16, infile);
	fread(pixels, 1, 115200, infile); // read in the image file

	printf("Size of file = %d\n", sizeOfFile); // Print out size of file

	int r, c; // rows, columns

	for (r = 0; r < 160 / 2; r++) {
		for (c = 0; c < 240 * 3; c++) {
			char temp = pixels[r][c]; // save the "higher" row in temp
			pixels[r][c] = pixels[159 - r][c];
			pixels[159 - r][c] = temp; // put the "lower" row into the "higher" row
		}
	}

	fwrite(header1, 1, 34, outfile);
	fwrite(&sizeOfFile, sizeof(int), 1, outfile);
	fwrite(header2, 1, 16, outfile);
	fwrite(pixels, 1, 115200, outfile); // read in the image file

	fclose(infile);
	fclose(outfile);

	return 0;
}

