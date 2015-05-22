/*
 * Duy Huynh
 * TCSS 333 - Spring '15
 * Assignment 4
 * list.c
 *
 * Implements a singly linked list that works specifically for adding
 * unique words and incrementing counters for duplicate words. This also
 * has functions for sorting nodes by descending order of word count differences
 * between two texts.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void swapNodes(Node*, Node*);

// Return the length of the linked list (also finds diffs)
int length(List *linkedList) {

    Node *currNode = linkedList->head;
    int count = 0;

    // Increment count for each node found.
    // Also determine word count diff to save O(n) time.
    while (currNode != NULL) {
        count++;
        currNode->diff = abs(currNode->count1 - currNode->count2);
        currNode = currNode->next;
    }
    return count;
}

// Return whether or not list is empty
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
        // Special case: Have to check the last node too...
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

// Sort by descending values of word count differences
void sortDescending(List *list) {

    // First determine the length of the list
    int listLength = length(list);

    // Entry point to list:
    Node *currNode = list->head;

    // Now bubble sort the list

    int i, j;
    for (i = 0; i < listLength - i; i++) {
        for (j = 0; j < listLength - i - 1; j++) {
            //Swap data between adjacent nodes if out of place
            if (currNode->diff < currNode->next->diff) {
                swapNodes(currNode, currNode->next);
            }
            currNode = currNode->next;
        }
        // Restart the sort at the beginning
        currNode = list->head;

    }

}

// Given two nodes, swap just their data.
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

// Print out ENTIRE linked list.
void printList(List *list) {
    Node *currNode = list->head;
    int i;
    while (currNode != NULL) {
        printf("%d) %s %d %d %d\n", i++, currNode->word, currNode->count1,
                currNode->count2, currNode->diff);
        currNode = currNode->next;
    }
}

