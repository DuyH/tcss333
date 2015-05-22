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

void swapNodes(Node*, Node*);

// Return the length of the linked list
int length(List *linkedList) {

    Node *currNode = linkedList->head;
    int count = 0;

    while (currNode != NULL) {
        count++;
        currNode->diff = abs(currNode->count1 - currNode->count2);
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

    // Setup a new node with passed data:
    Node *newNode = malloc(sizeof(Node));

    // Set the new node's word:
    newNode->word = word;
    newNode->next = NULL; // Do i need this? Better safe than sorry.

    // Increment correct word count for new node:
    if (whichText == 1) {
        newNode->count1 = 1;
        newNode->count2 = 0; // Crucial to initialize!
        // Because if I don't, chance that garbage number is there
        // if word only appears in text 1 + vice-versa.
    } else {
        newNode->count2 = 1;
    }

    // Iterate through each node, checking for word duplicates
    Node *currNode = list->head;
    if (currNode != NULL) {
        while (currNode->next != NULL) {
            // Check for word duplicate and update counts
            if (strcmp(currNode->word, word) == 0) {
                if (whichText == 1) {
                    currNode->count1++;
                } else {
                    currNode->count2++;
                }
                free(newNode);
                return;
            }
            // Move on to next node:
            currNode = currNode->next;
        }
        // Have to check the last node too...
        if (strcmp(currNode->word, word) == 0) {
            if (whichText == 1) {
                currNode->count1++;
            } else {
                currNode->count2++;
            }
            free(newNode);
            return;
        }

        // Word not found, so append new node onto tail
        currNode->next = newNode;

    } else { // list was empty initially
        list->head = newNode;

    }
}

void sortDescending(List *list) {

    // First determine the length of the list
    int listLength = length(list);

    // Entry point to list:
    Node *currNode = list->head;

    // Now bubble sort the list

    int i, j, k;
    for (i = 0; i < listLength; i++) {

        for (j = 0; j < listLength - i - 1; j++) {

            if (currNode->diff < currNode->next->diff) {
                //switch data
                swapNodes(currNode, currNode->next);
            }
            currNode = currNode->next;

        }
        currNode = list->head;

    }

}

// Given two nodes, swap their data.
void swapNodes(Node* node1, Node* node2) {

    // Swap the words
    char *tempWord = node1->word;
    node1->word = node2->word;
    node2->word = tempWord;

    // Swap count1
    int tempCount = node1->count1;
    node1->count1 = node2->count1;
    node2->count1 = tempCount;

    // Swap count2
    tempCount = node1->count2;
    node1->count2 = node2->count2;
    node2->count2 = tempCount;

    // Swap diff
    tempCount = node1->diff;
    node1->diff = node2->diff;
    node2->diff = tempCount;

}

void printList(List *list) {
    Node *currNode = list->head;
    int i;
    while (currNode != NULL) {
        printf("%d) %s %d %d %d\n", i++, currNode->word, currNode->count1,
                currNode->count2, currNode->diff);
        currNode = currNode->next;
    }
    printf("==============\n");

}

