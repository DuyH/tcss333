/*
 * Duy Huynh
 * TCSS 333 - Spring '15
 * Assignment 4
 * customer_purchases.c
 *
 * This program reads in a txt file of customer and their
 * item purchases. The program will then output two separate
 * files; one listing customers' chronological purhcases,
 * and the other listing highest purchase values first.
 * This assignment is to practice using structs and passing
 * them as pointers to functions.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 29
#define MAX_CUSTOMERS 20
#define MAX_ITEMS 10

typedef struct item Item;
typedef struct customer Customer;

// Contains details about a purchased item.
struct item {
    char itemName[MAX_NAME_LENGTH]; //29bytes
    int numOrdered; // 4bytes
    double price; //8bytes
    double totalValue;
};

// Contains customer info and purchases.
struct customer {
    char name[MAX_NAME_LENGTH];
    int itemCount;
    Item purchases[MAX_ITEMS];
    double totalOrder;
};

// Main for hw4.
int main(void) {

    setvbuf(stdout, NULL, _IONBF, 0);

    // Create an aray of Customer structs
    Customer clientele[MAX_CUSTOMERS] = { };
    int numOfUniqueCustomers = 0;

    readFile(clientele, &numOfUniqueCustomers);

    // Create time file FIRST!:
    generateTimeFile(clientele, &numOfUniqueCustomers);

    // Create money file after sorting:
    sortItems(clientele, &numOfUniqueCustomers);
    sortCustomersByTotal(clientele, &numOfUniqueCustomers);
    generateMoneyFile(clientele, &numOfUniqueCustomers);
    return 1;
}

// Read in a txt file containing customer purchases.
void readFile(Customer *clientele, int *numOfUniqueCustomers) {

// Take input file:
    FILE *inputFile = fopen("hw4input.txt", "r");

    // Declare the variables needed for reading each line
    char customer[MAX_NAME_LENGTH];
    int qty = 0;
    char item[MAX_NAME_LENGTH];
    float price;

    //Process each line until end-of-file reached
    while (!feof(inputFile)) {

        // Initialize the data for the line
        fscanf(inputFile, "%s%d%s $%f", customer, &qty, item, &price);

        // Create the customer-struct
        Customer newCustomer = { };
        strcpy(newCustomer.name, customer);
        newCustomer.itemCount = 0;

        // Create the item-struct + add to customer
        Item tempItem;
        strcpy(tempItem.itemName, item);
        tempItem.numOrdered = qty;
        tempItem.price = price;

        // Add the customer and its items to respective arrays
        addCustomer(clientele, numOfUniqueCustomers, newCustomer, tempItem);
    }
}

// Adds the given customer and item to their respective arrays
void addCustomer(Customer *clientele, int *numOfUniqueCustomers,
        Customer newCustomer, Item newItem) {

    int i; // Holds the customer's order in the array
    int addPerson = 1; // A flag for adding person or not

    for (i = 0; i < (*numOfUniqueCustomers); i++) {

        // Check if this name is already here:
        if (strcmp(clientele[i].name, newCustomer.name) == 0) {
            addPerson = 0;
            break;
        }
    }

    // Add customer if not already in array
    if (addPerson) {
        // Add the customer
        strcpy(clientele[i].name, newCustomer.name);
        (*numOfUniqueCustomers)++;
    }

    //Add the customer's item purchase in the right spot:
    strcpy(clientele[i].purchases[clientele[i].itemCount].itemName,
            newItem.itemName);
    clientele[i].purchases[clientele[i].itemCount].numOrdered =
            newItem.numOrdered;
    clientele[i].purchases[clientele[i].itemCount].price = newItem.price;
    clientele[i].purchases[clientele[i].itemCount].totalValue = newItem.price
            * newItem.numOrdered;
    clientele[i].itemCount++;
}

// Sort customers by descending value of their total purchases.
void sortItems(Customer *clientele, int *numOfUniqueCustomers) {

    // Bubble sort the prices, swapping Item pointers as needed
    int i, j, k;

    // Bubble sort each customer:
    for (i = 0; i < *numOfUniqueCustomers; i++) {

        // Bubble sort through the list of purchases
        for (j = 0; j < clientele[i].itemCount; j++) {
            for (k = 0; k < clientele[i].itemCount - 1; k++) {

                // Find the totals of adjacent purchases
                int total1 = clientele[i].purchases[k].numOrdered
                        * clientele[i].purchases[k].price;
                int total2 = clientele[i].purchases[k + 1].numOrdered
                        * clientele[i].purchases[k + 1].price;

                // Swap to satisfy highest total first
                if (total1 < total2) {
                    Item tempItem = clientele[i].purchases[k];
                    clientele[i].purchases[k] = clientele[i].purchases[k + 1];
                    clientele[i].purchases[k + 1] = tempItem;
                }
            }
        }
    }

}

// Sort customers by descending value of item values.
void sortCustomersByTotal(Customer *clientele, int *numUniqueCustomers) {

    // First find the total order for each customer:
    int i, j;
    for (i = 0; i < *numUniqueCustomers; i++) {
        for (j = 0; j < clientele[i].itemCount; j++) {
            clientele[i].totalOrder += clientele[i].purchases[j].totalValue;
        }
    }

    // Now bubble sort the list by descending total order
    int l;
    for (l = 0; l < *numUniqueCustomers; l++) {
        for (i = 0; i < *numUniqueCustomers; i++) {

            for (j = 0; j < *numUniqueCustomers - 1; j++) {
                double total1 = clientele[i].totalOrder;
                double total2 = clientele[i + 1].totalOrder;

                // Swap if first customer has smaller total order than adjacent
                if (total1 < total2) {
                    Customer tempCustomer = clientele[i];
                    clientele[i] = clientele[i + 1];
                    clientele[i + 1] = tempCustomer;
                }
            }
        }
    }

}

// Generate a txt file of customers and purchases in chronological order.
void generateTimeFile(Customer *clientele, int *numOfUniqueCustomers) {

    FILE *outputTime = fopen("hw4time.txt", "w");
    int i;
    for (i = 0; i < *numOfUniqueCustomers; i++) {

        // Print the customer's name
        fprintf(outputTime, "%s\r\n", clientele[i].name);

        // Print each item for a customer:
        int j;
        for (j = 0; j < clientele[i].itemCount; j++) {
            fprintf(outputTime, "%s %d $%.2f\r\n",
                    clientele[i].purchases[j].itemName,
                    clientele[i].purchases[j].numOrdered,
                    clientele[i].purchases[j].price);
        }
        fprintf(outputTime, "\r\n"); // use \r so notepad will line break correctly!
    }
    fclose(outputTime); // Remember to close the stream

}

// Generate a txt file of customers and purchases by descending total order value
void generateMoneyFile(Customer *clientele, int *numOfUniqueCustomers) {

    FILE *outputMoney = fopen("hw4money.txt", "w");
    int i;
    for (i = 0; i < *numOfUniqueCustomers; i++) {

        // Print the customer's name
        fprintf(outputMoney, "%s, Total Order = $%.2f\r\n", clientele[i].name,
                clientele[i].totalOrder); // note \r so notepad will line break!

        // Print each item for a customer:
        int j;
        for (j = 0; j < clientele[i].itemCount; j++) {
            fprintf(outputMoney, "%s %d $%.2f, Item Value = $%.2f\r\n",
                    clientele[i].purchases[j].itemName,
                    clientele[i].purchases[j].numOrdered,
                    clientele[i].purchases[j].price,
                    clientele[i].purchases[j].totalValue);

        }
        fprintf(outputMoney, "\r\n");
    }
    fclose(outputMoney); // Remember to close the stream
}
