/*
 * Duy Huynh
 * TCSS 333 - Spring '15
 * Assignment 4
 * list.h
 *
 * Header file for list.c. For implementation of a singly linked list.
 * Features a list composed of nodes containing a char array, two word
 * counts, a differences count and next node pointer. This linked list
 * implements length, isEmpty, adding a word (essentially a node),
 * and sorting of nodes.
 *
 */

#ifndef LIST_H_
#define LIST_H_

// struct representing a node in the linked list.
struct node {
    char *word;
    int count1;
    int count2;
    int diff;
    struct node *next;
};

typedef struct node Node;

// Representing a linked list.
struct list {
    Node *head;
};

typedef struct list List;

// Function of this linked list
int length(List *); // number of elements in list.
int isEmpty(List *); // 0 not empty.
void addWord(List *list, char *word, int text); // Add node to list
void sortDescending(List *); // Sort by word freq diff.
void printList(List *); // Print each word

#endif /* LIST_H_ */

