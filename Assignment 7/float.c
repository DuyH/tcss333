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
    return f;
}

void printFloat(float f) {

    // Print number in float:
    printf("Your float was read as: %f\n", f);

    // Print number in 32 bits:
    printf("Your float in 32 bits: ");
    unsigned int bin;
    int k;
    for (k = 0; k < 32; k++) {
        if (bin & 0x80000000) {
            printf("1");
        } else {
            printf("0");
        }
        bin = bin << 1;
    }

    // Print the sign:
    printf("Sign: ");
    if()

}

