/*
 * main.c
 *
 *  Created on: Apr 2, 2015
 *      Author: Duy
 */

#include <stdio.h>

#define MAX 20

//function prototypes:
double binToDec(char binary[]);
void decToBin(double answer);
double operate(char c, double operand1, double operand2);

int main(void) {

	// John recommended to put this as first line:
	setvbuf(stdout, NULL, _IONBF, 0);

	// Read the next non-space character

	while (1) {

		char op;
		double operand1;
		double operand2;
		double answer;
		char firstNumString[MAX];
		char secNumString[MAX];

		// Store first operand string
		scanf("%s", firstNumString);

		//check first letter of string for 'q' to quit program
		if (firstNumString[0] == 'q' || secNumString[0] == 'Q') {
			break;
		}

		// Store the operator character
		scanf(" %c", &op);

		// Store the second operand string
		scanf(" %s", secNumString);

		// Convert first binary operand to decimal
		operand1 = binToDec(firstNumString);

		// Convert second binary operand to decimal
		operand2 = binToDec(secNumString);

		// Perform the operation
		answer = operate(op, operand1, operand2);
		printf("%f\n", answer);

		// Convert back to binary and print
		decToBin(answer);

	}

	return 0;
}

double binToDec(char binary[]) {

	double sum = 0;
	double power = 1;
	for (int i = 0; i < MAX; i++) {

		if (binary[i] == '.') {
			power = 0.5;
			continue;
		}

		if (power == 1) {
			sum *= 2;
			if (binary[i] == '1') {
				sum++;
			}
		} else {
			if (binary[i] == '1') {
				sum += power;
			}
			power /= 2;
		}
	}

	return sum;
}

double operate(char operation, double operand1, double operand2) {

// Perform the operation according to c
	switch (operation) {
	case '+':
		return operand1 + operand2;
		break;
	case '-':
		return operand1 - operand2;
		break;
	case '*':
		return operand1 * operand2;
		break;
	case '/':
		return operand1 / operand2;
		break;
	default:
		return 0;
		break;
	}
	return 0;
}

void decToBin(double answer) {

	double power = 1;

	// Decimal to Binary algorithm:

	// Step 1: Find power of 2 greater than the number.
	while (answer >= power) {
		power *= 2;
	}

	// Step 2: Divide that power of 2 in half.
	power /= 2;

	// Step 3: Output binary for left-hand side.

	// If there are no 1's on the left, at least print a 0:
	if (answer < 1) {
		printf("0");
		// "1" when you can subtract the current power from the answer.
		// "0" if you cannot.
		// Either way, divide the current power of 2 in half.
	} else {
		while (power >= 1) {
			if (answer >= power) {
				printf("1");
				answer -= power;
			} else {
				printf("0");
			}
			power /= 2;
		}

	}

	// Step 4: Write the binary decimal point.
	printf(".");

	// Step 5:
	power = 0.5;

	// Print at least one digit if no fractional:
	if (answer == 0) {
		printf("0");
	}

	for (int i = 0; i < MAX; i++) {

		if (answer >= power) {
			printf("1");
			answer -= power;
		} else if (answer == 0) {
			break;
		} else {
			printf("0");
		}
		power /= 2;
	}
	printf("\n");

}

