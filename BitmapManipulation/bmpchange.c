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

	char header[54]; // bmp file header
	char pixels[160][240 * 3]; //[rows][cols]
	// 240*3 bc 3 is #bytes per pixel

	fread(header, 1, 54, infile);
	fread(pixels, 1, 115200, infile); // read in the image file

	int r, c; // rows, columns

	for (r = 0; r < 160; r++) {
		for (c = 0; c < 240 * 3; c += 3) {
			char temp;
			temp = pixels[r][c];
			pixels[r][c] = pixels[r][c + 1];
			pixels[r][c + 1] = temp;
		}
	}

	// sizeof(char) tells you the size (bytes) of the type given
	fwrite(header, sizeof(char), 54, outfile); // write out the image file
	fwrite(pixels, sizeof(char), 115200, outfile);

	fclose(infile);
	fclose(outfile);

	return 0;
}

