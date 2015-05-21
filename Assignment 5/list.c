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

Node* locateWord(List*, char*);

void initializeList(List *linkedList) {
    linkedList->head = NULL;
}

// Return the length of the linked list
int length(List *linkedList) {

    Node *tempNode = linkedList->head;
    int count = 1;

    // If head is null, return 0
    if (linkedList->head == NULL) {
        return 0;
    } else {
        // Otherwise increment for every node then return
        while (tempNode->next != NULL) {
            count++;
            tempNode = tempNode->next;
        }
        return count;
    }
}

// Return if empty...
int isEmpty(List *linkedList) {

    return linkedList->head == NULL;

    /*// Possibly unneeded, if above works
     if (linkedList->head == NULL) {
     return 1;
     } else {
     return 0;
     }
     */
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

    /*
     // Iterate until we get to last node
     while (tempNode->next != NULL) {
     tempNode = tempNode->next;
     }
     tempNode->next = newNode;
     */
}

void printList(List *list) {
    Node *tempNode = list->head;

    if (tempNode == NULL) {
        return;
    }

    printf("Word: %s\n", tempNode->word);

    while (tempNode->next != NULL) {
        tempNode = tempNode->next;
        printf("Word: %s\n", tempNode->word);
    }
}

