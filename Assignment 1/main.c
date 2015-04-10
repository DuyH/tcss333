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
double operate(char c);

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

	bin2float();
	//scanf(" %c ", &operator);
	//printf("%c", operator);

	// Store

	// Echos c
	//printf("%c", c);

	return 0;
}

double bin2float() {

	float sum = 0;
	char c;

	while (scanf(" %c", &c)) {
		sum *= 2;
		if (c == '1') {
			printf("1!");
			sum += 1;
		}
		if (c == '.') {

			float power = 1.0;
			while (scanf(" %s", &c)) {
				power /= 2;
				if (c == '1') {
					sum += power;
					printf("1!");
				} else if (c == '0') {
					printf("0!");
				}
			}
			printf("exited period while loop\n");

		}
	}
	printf("Exited!");
	printf("%f", sum);

	return sum;
}

double operate(char c, float operand1, float operand2) {

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

