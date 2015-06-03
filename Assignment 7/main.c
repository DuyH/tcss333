/*
 * Duy Huynh
 * TCSS 333 - Spring '15
 * Assignment 7
 * main.c
 *
 * This program reads in a float from console and displays
 * how that float was derived via IEEE-754 formatting.
 *
 */

#include<stdio.h>
#include<stdlib.h>

#define EXPO 8
#define MANTISSA 23
#define BIAS 127
typedef union ufloat Float;

float getFloat();
void printFloat(Float*);
float printCreateFraction(Float*);
float printApplyExponent(Float*, float);

union ufloat {
    float f;
    unsigned int u;
};

// Main
int main(void) {

    // Allow (Windows machine) to print correctly
    setbuf(stdout, NULL);

    // Create a union that holds float and can be read as int
    Float *myFloat = malloc(sizeof(Float));

    // Get a float from console input:
    myFloat->f = getFloat();

    // Print the data about the float:
    printFloat(myFloat);
    printf("\n");

    // Print out fraction creation
    float fractionalPart = printCreateFraction(myFloat);
    printf("\n");

    // Print out exponent creation
    float answer = printApplyExponent(myFloat, fractionalPart);
    printf("\n");

    // Apply the sign
    answer *= myFloat->u & 0x80000000 ? -1 : 1;

    // Print the answer
    printf("Final Answer: %f", answer);

}

// Retrieve a float number from console input
float getFloat() {
    printf("Enter a float: ");
    float temp;
    scanf("%f", &temp);
    return temp;
}

void printFloat(Float *myFloat) {
    printf("Your float was read as: %f\n", myFloat->f);

    // Print float in 32bits
    printf("Your float in 32 bits: ");
    int k;
    unsigned int temp = myFloat->u;
    for (k = 0; k < sizeof(float) * 8; k++) {
        printf("%d", temp & 0x80000000 ? 1 : 0);
        temp <<= 1;
    }
    printf("\n");

    // Print Sign
    temp = myFloat->u;
    printf("Sign: %d", temp & 0x80000000 ? 1 : 0);
    temp <<= 1;
    printf("\n");

    // Print Exponent
    printf("Exponent: ");
    for (k = 0; k < EXPO; k++) {
        printf("%d", temp & 0x80000000 ? 1 : 0);
        temp <<= 1;
    }
    printf("\n");

    // Print Fraction
    printf("Fraction: ");
    for (k = 0; k < MANTISSA; k++) {
        printf("%d", temp & 0x80000000 ? 1 : 0);
        temp <<= 1;
    }
    printf("\n");
}

float printCreateFraction(Float *floatNum) {

    unsigned int fractionBinary = floatNum->u;
    float fractionFloat = 1;
    float power = 1;

    printf("Creating the fraction:\n");
    printf("fraction = %f (the implicit 1)\n", fractionFloat);

    // Shift until we hit the fractional part in binary
    int i;
    for (i = 0; i < EXPO + 1; i++) {
        fractionBinary <<= 1;
    }

    // Now create the fraction:
    for (i = 0; i < MANTISSA; i++) {
        power /= 2;
        printf("fraction = ");
        if (fractionBinary & 0x80000000) {
            fractionFloat += power;
            printf("%f, after adding %f\n", fractionFloat, power);
        } else {
            printf("%f, after skipping %f\n", fractionFloat, power);
        }
        fractionBinary <<= 1;
    }

    return fractionFloat;
}

float printApplyExponent(Float *floatNum, float fractionalPart) {

    unsigned int exponentBinary = floatNum->u;
    unsigned int exponentDecimal = 0;
    int power = 1;
    float temp = fractionalPart;

    // Apply the exponent
    printf("Applying the exponent:\n");

    //Find exponent portion in decimal
    int i;
    for (i = 0; i < EXPO; i++) {
        exponentDecimal += 0x00800000 & exponentBinary ? power : 0;
        exponentBinary >>= 1;
        power *= 2;
    }

    // Determine the unbiased exponent
    int unbiasedExponent = exponentDecimal - 127;
    printf("unbiased exponent = %d\n", unbiasedExponent);

    // If negative unbiased exponent, divide:
    if (unbiasedExponent < 0) {
        unbiasedExponent *= -1;
        for (i = 0; i < unbiasedExponent; i++) {
            temp /= 2;
            printf("divided by 2 = %f\n", temp);
        }
    } else { // Otherwise multiply if positive unbiased exponent
        for (i = 0; i < unbiasedExponent; i++) {
            temp *= 2;
            printf("times 2 = %f\n", temp);
        }
    }

    return temp;
}

