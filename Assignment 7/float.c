/*
 * float.c
 *
 *  Created on: Jun 1, 2015
 *      Author: duy
 */

#include <stdio.h>
#include <stdlib.h>
float getFloat();
void printFloat(float);

int main(void) {

    float f = getFloat();
    printFloat(f);

    return 1;
}

float getFloat() {

    float f;
    printf("Enter a float: ");
    scanf("%f", &f);
    printf("%f\n", f);
    printf("%d\n", f);
    printf("%x\n", f);
    return f;
}

void printFloat(float f) {

    // Print number in float:
    printf("Your float was read as: \n");

    // Print number in 32 bits:
    printf("Your float in 32 bits: ");
    unsigned int bin = f;
    int k;
    for (k = 0; k < 64; k++) {
        if (bin & 0x80000000) {
            printf("1");
        } else {
            printf("0");
        }
        bin = bin << 1;
    }

    // Print the sign:
    printf("\nSign: ");
    unsigned int sign, expo, fraction;
    bin = f;
    sign = (bin & 0x80000000) ? 1 : 0;
    printf("%d", sign);

    // Printf the exponent:
    printf("\nExponent: ");
    for (k = 0; k < 8; k++) {
        printf("%d", (bin & 0x40000000) ? 1 : 0);
        bin = bin << 1;
    }

//Print the fraction:

}

