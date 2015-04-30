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

struct product_tag {

    char itemName[MAX_NAME_LENGTH];
    int numOrdered;
    double price;

};

typedef struct product_tag Product;

struct customer_tag {

    char name[MAX_NAME_LENGTH];
    Product purchases[MAX_ITEMS];
    int numItems;

};

typedef struct customer_tag Customer;

int main(void) {

    setvbuf(stdout, NULL, _IONBF, 0);

// Create
    return 1;
}

void printCustomer(Customer cust) {
    printf("%s,", cust.name);
}

void addCustomer(Customer newCustomer, Customer clientele[], int *custCount) {
    clientele[*custCount] = newCustomer;
    (*custCount)++;
}

void readFile() {

// Take input file:
    FILE *inputFile = fopen("hw4input.txt", "r");

}

void
