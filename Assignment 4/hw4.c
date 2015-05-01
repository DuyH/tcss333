/*
 * hw4.c
 *
 *  Created on: Apr 27, 2015
 *      Author: duy
 */

#include <stdio.h>

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
    int numItems;

};

typedef struct customer Customer;

int main(void) {

    setvbuf(stdout, NULL, _IONBF, 0);

    readFile();

// Create
    return 1;
}

void readFile() {

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

        // Check if customer has already been created or not:
        // If not, add the customer to the array of customer-structs
        // If so just skip

        // Create the item-struct

        // While we're at this customer, add the item
    }

}

int addCustomer(char *) {
    int flag = 0;
}

