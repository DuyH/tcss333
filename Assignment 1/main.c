/*
 * main.c
 *
 *  Created on: Apr 2, 2015
 *      Author: Duy
 */

#include <stdio.h>

//function prototypes:
double bin2float(void);
void float2bin(void);
double addition(double operand1, double operand2);
double subtraction(double operand1, double operand2);
double multiplication(double operand1, double operand2);
double division(double operand1, double operand2);
void selectOperator(char c);

//vars
#define TRUE 1;
#define FALSE 0;

int main(void) {

	// John recommended to put this as first line:
	setvbuf(stdout, NULL, _IONBF, 0);

	char c;
	double operand1;
	double operand2;
	char operator;

	// Scans a line
	while (scanf("%c", &c) == 1) {

		operand1 = bin2float();

		// Store

	}

	// Echos c
	//printf("%c", c);

	return 0;
}

void selectOperator(char c) {

	//Check the operator then redirect to correct operation function:
	if (c == '+' || c == '-' || c == '*' || c == '/') {

		char operator = c;

		switch (c) {
		case '+':
			printf("Addition!");
			break;
		case '-':
			printf("Subtraction!");
			break;
		case '*':
			printf("Multiplication!");
			break;
		case '/':
			printf("Division!");
			break;
		default:
			//code:
			break;
		}
	}

}

