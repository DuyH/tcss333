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
    FILE *blendFile = fopen("blend.bmp", "wb"); // wb  = write binary
    FILE *checkerFile = fopen("checker.bmp", "wb"); // wb  = write binary

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
    unsigned char blendPixArr[height][width * 3];

    // A pixel array for checker
    unsigned char checkerPixArr[height][width * 3];

    // BLEND them pixels!
    int r, c; // rows, columns

    for (r = 0; r < height; r++) {
        for (c = 0; c < width * 3; c++) {
            blendPixArr[r][c] = (pixelsIn1[r][c] + pixelsIn2[r][c]) / 2;
        }
    }

    // CHECKER them pixels!

    int flag = 0;

    for (r = 0; r < height; r++) {
        for (c = 0; c < width * 3; c++) {
            if (c % (width * 3 / 8) == 0) {
                flag++;
            }
            if (flag % height == 0) {
                flag++;
            }
            if (flag % 2 == 0) {
                checkerPixArr[r][c] = pixelsIn1[r][c];
            } else {
                checkerPixArr[r][c] = pixelsIn2[r][c];
            }

        }
    }

    // Write to outfile1 (blend.bmp)
    fwrite(header1, 1, 18, blendFile);
    fwrite(&width, sizeof(int), 1, blendFile);
    fwrite(&height, sizeof(int), 1, blendFile);
    fwrite(header2, 1, 28, blendFile);
    fwrite(blendPixArr, 1, imageSize, blendFile); // read in the image file

    // Write to outfile2 (checkered.bmp)
    fwrite(header1, 1, 18, checkerFile);
    fwrite(&width, sizeof(int), 1, checkerFile);
    fwrite(&height, sizeof(int), 1, checkerFile);
    fwrite(header2, 1, 28, checkerFile);
    fwrite(checkerPixArr, 1, imageSize, checkerFile); // read in the image file

    fclose(infile1);
    fclose(infile2);

    fclose(blendFile);
    fclose(checkerFile);

    return 0;
}

