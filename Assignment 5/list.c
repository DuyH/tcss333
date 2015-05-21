/*
 * list.c
 *
 *  Created on: May 18, 2015
 *      Author: duy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void initializeList(List *linkedList) {
    linkedList->head = NULL;
}

// Return the length of the linked list
int length(List *linkedList) {

    Node *currNode = linkedList->head;
    int count = 0;

    while (currNode != NULL) {
        count++;
        currNode = currNode->next;
    }
    return count;
}

// Return if empty...
int isEmpty(List *linkedList) {
    return linkedList->head == NULL;
}

// Add a word to the list and update count
void addWord(List *list, char *word, int whichText) {

    // Create new node to add
    Node *newNode = malloc(sizeof(Node));

    // Put word into node
    newNode->word = word;
    newNode->next = NULL; // Do i need this?
    // set appropriate count to 1
    if (whichText == 1) {
        newNode->count1 = 1;
    } else {
        newNode->count2 = 1;
    }
    Node *tempNode = list->head;

    if (tempNode == NULL) {
        list->head = newNode;
    } else {
        while (tempNode->next != NULL) {
            if (strcmp(tempNode->next->word, word) == 0) {
                if (whichText == 1) {
                    tempNode->count1++;
                } else {
                    tempNode->count2++;
                }
                free(newNode);
                return;
            }
            tempNode = tempNode->next;
        }
        // tempNode is now Null, and we didn't find the word! so...
        tempNode->next = newNode;

    }
}

void printList(List *list) {
    Node *currNode = list->head;
    while (currNode != NULL) {
        printf("Word: %s\n", currNode->word);
        currNode = currNode->next;
    }
}

