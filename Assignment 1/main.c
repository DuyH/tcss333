/*
 * main.c
 *
 *  Created on: Apr 2, 2015
 *      Author: Duy
 */

#include <stdio.h>

//function prototypes:
double bin2float(char c, double operand);
void float2bin(void);
double operate(char c, double operand1, double operand2);

int main(void) {

	// John recommended to put this as first line:
	setvbuf(stdout, NULL, _IONBF, 0);

	char c;
	double operand1;
	double operand2;
	char operator;

	int rightSide = 0;

	// Read the next non-space character

	while (1) {

		scanf(" %c", &c);

		if (!rightSide) {

			printf("works!");
			operand1 = bin2float(c, operand1);
		}
		operand1 = bin2float();
		printf("%f", operand1);
		c = scanf(" %c", &c);

		printf(&c);
		printf("apples");
		operand2 = bin2float();

		// Quit on 'q'
		if (c == 'q') {
			printf("EXITING!");
			break;
		}
	}

	return 0;
}

double bin2float() {

	float sum = 0;
	char c;

//Read the left-hand side
	while (1) {

		//Break out of left-hand side summation if decimal detected:
		if (c == '.') {
			break;
		}

		// If 1, add to the running sum:
		sum *= 2;
		if (c == '1') {
			sum += 1;
		}
	}

// Now that the decimal has been detected...
	while (1) {
		double power = 1.0;
		scanf(" %c", &c);
		power /= 2;
		if (c == '1') {
			sum += power;
		}

		if (c == '+' || c == '-' || c == '*' || c == '/') {
			printf(&c);
			break;
		}

	}

	return sum;
}

double operate(char c, double operand1, double operand2) {

//Check the operator then redirect to correct operation function:
	if (c == '+' || c == '-' || c == '*' || c == '/') {

		switch (c) {
		case '+':
			printf("Addition!");
			return operand1 + operand2;
			break;
		case '-':
			printf("Subtraction!");
			return operand1 - operand2;
			break;
		case '*':
			printf("Multiplication!");
			return operand1 * operand2;
			break;
		case '/':
			printf("Division!");
			return operand1 / operand2;
			break;
		default:
			//code:
			break;
		}
	}

}

