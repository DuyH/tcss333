/*
 * list.c
 *
 *  Created on: May 18, 2015
 *      Author: duy
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    char *word;
    int count1;
    int count2;
    struct node *next;
};

typedef struct node Node;

