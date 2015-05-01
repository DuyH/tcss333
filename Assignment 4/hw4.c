/*
 * hw4.c
 *
 *  Created on: Apr 27, 2015
 *      Author: duy
 */

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 29
#define MAX_CUSTOMERS 20
#define MAX_ITEMS 10

void readFile();

void createMoneyFile();
void createTimeFile();

void writeOneMoney();
void writeOneTime();

void sortByPurchase();
void sortByTime();

struct item {

	char itemName[MAX_NAME_LENGTH];
	int numOrdered;
	double price;

};

typedef struct item Item;

struct customer {

	char name[MAX_NAME_LENGTH];
	Item purchases[MAX_ITEMS];
	int itemCount;

};

typedef struct customer Customer;

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);

	// Create an aray of Customer structs
	Customer clientele[MAX_CUSTOMERS];

	readFile(clientele);

// Create
	return 1;
}

void readFile(Customer *clientele[MAX_CUSTOMERS]) {

// Take input file:
	FILE *inputFile = fopen("hw4input.txt", "r");

	// Declare the variables needed for reading each line
	char customer[MAX_NAME_LENGTH];
	int qty;
	char item[MAX_NAME_LENGTH];
	float price;

	while (!feof(inputFile)) { //while not end of file

		// Acquire the data:
		fscanf(inputFile, "%s%d%s $%f", customer, &qty, item, &price);
		printf("%s %d %s $%.2f", customer, qty, item, price);
		printf("\n");

		// Create the customer-struct
		Customer tempCustomer;
		strcpy(tempCustomer.name, customer);
		tempCustomer.itemCount++; // ++ customer's #of unique items

		// addCustomer(return the index of the customer in the CustomerstructArray)

		// Create the item-struct + add to customer
		Item tempItem;
		strcpy(tempItem.itemName, item);
		tempItem.numOrdered = qty;
		tempItem.price = price;
		tempCustomer.purchases[0] = tempItem;

		printf("%s %d %s $%.2f\n", tempCustomer.name, tempItem.numOrdered,
				tempItem.itemName, tempItem.price);

		// add Customer to array?
		// add Item to aray?

	}
}

int addCustomer(Customer *clientele[MAX_CUSTOMERS], Customer newCustomer) {

	// Search for the customer
	int i;
	for (i = 0; i < MAX_CUSTOMERS; i++) {
		// If the Customer name is found, then exit
		if (strcmp(clientele[i]->name, newCustomer.name)) {

		}

	}
}

