/*
 * mallok.c
 *
 *  Created on: May 28, 2015
 *      Author: Duy Huynh
 */

#include <stdio.h>
#include <stdlib.h>
#include "mallok.h"

// Private heap
static Block *wholeBlock;
static Block *headBlock;
static int sizeCounter;

void create_pool(int size) {

    // Allocate space for private heap
    wholeBlock = malloc(size);
    headBlock = malloc(size);
    int sizeCounter = size;

    // Set up head block
    headBlock->startAddress = wholeBlock;
    headBlock->free = TRUE;
    headBlock->next = NULL;
    headBlock->size = 0;

    // Set up initial block
    wholeBlock->startAddress = wholeBlock;
    wholeBlock->free = TRUE;
    wholeBlock->next = NULL;

}
void *my_malloc(int size) {

    // Requested size is larger than private heap:
    if (sizeCounter < size) {
        return NULL;
    }

    // If nothing in private heap yet:
    if (headBlock->size == 0) {
        headBlock->size = size;
        headBlock->free = FALSE;
        sizeCounter -= size;
        return NULL;
    }

    // Start with
    Block *ptr = headBlock;

    // Point to next free block
    while (!ptr->free) {
        ptr = ptr->next;
        sizeCounter -= ptr->size;
    }

    // We are at free block now
    if (ptr->size >= size) { // Check if request size smaller
        ptr->free = FALSE;
        ptr->size = ptr->size - size;
        // Create new block
        Block *newBlock = malloc(sizeof(Block));
        ptr->next = newBlock;
        newBlock->size = size;
        newBlock->free = FALSE;
        newBlock->next = NULL;
    }

}
void my_free(void *block) {

}
