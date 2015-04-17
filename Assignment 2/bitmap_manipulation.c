/*
 * Duy Huynh
 * TCSS 333 - Spring '15
 * Assignment 2
 * bitmap_manipulation.c
 *
 * This program takes two bitmap images as input and outputs
 * two bitmaps; one that has pixel data with RGB values averaged
 * between the two input images and one that has a checkered pattern
 * of the two images. The checkered image is 8x8.
 *
 */

#include <stdio.h>

int main(void) {

    FILE *imgFile1 = fopen("in1.bmp", "rb"); // rb = readbinary
    FILE *imgFile2 = fopen("in2.bmp", "rb"); // rb = readbinary
    FILE *imgBlend = fopen("blend.bmp", "wb"); // wb  = write binary
    FILE *imgChecker = fopen("checker.bmp", "wb"); // wb  = write binary

    // Reading in the header of the first image (54 bytes):
    char header1[18]; // bmp file header (before the file width)
    fread(header1, 1, 18, imgFile1);

    // Width of image:
    int width;
    fread(&width, sizeof(int), 1, imgFile1);

    // Height of image:
    int height;
    fread(&height, sizeof(int), 1, imgFile1);

    // The rest of the header, up to the 54th bit:
    char header2[28];
    fread(header2, 1, 28, imgFile1);

    int imageSize = width * height * 3;

    // Store pixel data of first image in pixelsIn1 2d-array
    unsigned char pixelsIn1[height][width * 3]; //[rows][cols]
    fread(pixelsIn1, 1, imageSize, imgFile1); // read in the image file

    // Store pixel data of second image in pixelsIn2 2d-array
    unsigned char pixelsIn2[height][width * 3];
    fseek(imgFile2, 54, SEEK_SET); // Skip 54 bits in the file
    fread(pixelsIn2, 1, imageSize, imgFile2); // Grab pixel data

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
    int flipFlag = 0;

    for (r = 0; r < height; r++) {
        for (c = 0; c < width * 3; c++) {

            // Changes img pixel source for width:
            if (c % (width * 3 / 8) == 0) {
                flipFlag++;
            }

            // Switch the source pixel array order for height:
            if (flipFlag % height == 0) { // Changes by row
                flipFlag++;
            }

            // Alternate img pixel source by even/odd flag:
            if (flipFlag % 2 == 0) {
                checkerPixArr[r][c] = pixelsIn1[r][c];
            } else {
                checkerPixArr[r][c] = pixelsIn2[r][c];
            }
        }
    }

    // Write to outfile1 (blend.bmp)
    fwrite(header1, 1, 18, imgBlend);
    fwrite(&width, sizeof(int), 1, imgBlend);
    fwrite(&height, sizeof(int), 1, imgBlend);
    fwrite(header2, 1, 28, imgBlend);
    fwrite(blendPixArr, 1, imageSize, imgBlend); // read in the image file

    // Write to outfile2 (checkered.bmp)
    fwrite(header1, 1, 18, imgChecker);
    fwrite(&width, sizeof(int), 1, imgChecker);
    fwrite(&height, sizeof(int), 1, imgChecker);
    fwrite(header2, 1, 28, imgChecker);
    fwrite(checkerPixArr, 1, imageSize, imgChecker); // read in the image file

    // Close the files after we're finished using them:
    fclose(imgFile1);
    fclose(imgFile2);

    fclose(imgBlend);
    fclose(imgChecker);

    return 0;
}

