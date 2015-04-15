/*
 * main.c
 *
 *  Created on: Apr 6, 2015
 *      Author: duy
 */

#include <stdio.h>

int main(void) {

    FILE *infile1 = fopen("in1.bmp", "rb"); // rb = readbinary
    FILE *infile2 = fopen("in2.bmp", "rb"); // rb = readbinary
    FILE *outfile1 = fopen("blend.bmp", "wb"); // wb  = write binary
    FILE *outfile2 = fopen("checker.bmp", "wb"); // wb  = write binary

    // Reading in the header of the first image (54 bytes):
    char header1[18]; // bmp file header (before the file width)
    fread(header1, 1, 18, infile1);

    int width;
    fread(&width, sizeof(int), 1, infile1);
    printf("Width: %d\n", width);

    int height;
    fread(&height, sizeof(int), 1, infile1);
    printf("Height: %d\n", height);

    char header2[28];
    fread(header2, 1, 28, infile1);

    int imageSize = width * height * 3;

    // Store pixel data of first image in pixelsIn1 2d-array
    unsigned char pixelsIn1[height][width * 3]; //[rows][cols]
    fread(pixelsIn1, 1, imageSize, infile1); // read in the image file

    // Store pixel data of second image in pixelsIn2 2d-array
    unsigned char pixelsIn2[height][width * 3];
    fseek(infile2, 54, SEEK_SET);
    fread(pixelsIn2, 1, imageSize, infile2);

    // A pixel array for blend
    unsigned char blendArr[height][width * 3];

    // A pixel array for checker
    unsigned char pixelsOut2[height][width * 3];

    // Blend them pixels!
    int r, c; // rows, columns

    for (r = 0; r < height; r++) {
        for (c = 0; c < width * 3; c++) {
            blendArr[r][c] = (pixelsIn1[r][c] + pixelsIn2[r][c]) / 2;
        }
    }

    // Write to outfile1 (blend.bmp)
    fwrite(header1, 1, 18, outfile1);
    fwrite(&width, sizeof(int), 1, outfile1);
    fwrite(&height, sizeof(int), 1, outfile1);
    fwrite(header2, 1, 28, outfile1);
    fwrite(blendArr, 1, imageSize, outfile1); // read in the image file

//	// Write to outfile2 (checkered.bmp)
//	fwrite(header1, 1, 34, outfile1);
//	fwrite(&width, sizeof(int), 1, outfile1);
//	fwrite(&height, sizeof(int), 1, outfile1);
//	fwrite(&imageSize, sizeof(int), 1, outfile1);
//	fwrite(header2, 1, 16, outfile1);
//	fwrite(pixelsIn1, 1, 115200, outfile1); // read in the image file

    fclose(infile1);
    fclose(infile2);

    fclose(outfile1);
    fclose(outfile2);

    return 0;
}

