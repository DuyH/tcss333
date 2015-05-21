/*
 * list.h
 *
 *  Created on: May 18, 2015
 *      Author: duy
 */

#ifndef LIST_H_
#define LIST_H_

struct node {
    char *word;
    int count1;
    int count2;
    struct node *next;
};

typedef struct node Node;

struct list {
    Node *head;
};

typedef struct list List;

void initializeList(List *); // Create empty list
int length(List *); // number of elements in list.
int isEmpty(List *); // 0 not empty.
void addWord(List *list, char *word, int text);
void sortDescending(List *); // Sort by word freq diff.
void printList(List *); // Print each word

#endif /* LIST_H_ */

