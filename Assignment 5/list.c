/*
 * list.c
 *
 *  Created on: May 18, 2015
 *      Author: duy
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void initializeList(List *linkedList) {
    linkedList->head = NULL;
}

// Return the length of the linked list
int length(List *linkedList) {

    Node *tempNode = linkedList->head;
    int count = 0;

    // If head is null, return 0
    if (tempNode == NULL) {
        return 0;
    } else {
        // Otherwise increment for every node then return
        while (tempNode != NULL) {
            count++;
            tempNode = tempNode->next;
        }
        return count;
    }
}

// Return if empty...
int isEmpty(List *linkedList) {

    if (linkedList->head == NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Add a word to the list and update count
void addWord(List *list, char *word, int whichText) {

    Node *tempNode = list->head;

}

