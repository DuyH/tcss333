/*
 * my_mallok.c
 *
 *  Created on: May 28, 2015
 *      Author: Duy
 */

/*
 * Nabil Fadili
 * TCSS 333A
 * March 3 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include "mallok.h"

static Block *mainBlock;
static Block *front;
static int totalBlocks = 0;      //counter for memBlocks not including mainBlock

void create_pool(int size) {
    mainBlock = malloc(size);
    mainBlock->start = mainBlock;
    mainBlock->size = size;
    mainBlock->free = TRUE;
    mainBlock->next = NULL;
    mainBlock->prev = NULL;
    front = mainBlock;
}

void *my_malloc(int size) {
    Block ptr = front;
    while (!ptr->free) {
        ptr = ptr->next;
    }
    //if (ptr->)
    if (size > mainBlock->size) {
        printf("Not enough memory to allocate.\n");
        return NULL;
    }
    if (size <= mainBlock->size) {  //greater than OR equal. keep an eye on this
        Block *newBlock = malloc(sizeof(Block));

        newBlock->start = mainBlock->start;
        mainBlock->start += size;

        mainBlock->size -= size;

        newBlock->size = size;
        newBlock->free = FALSE;

        newBlock->next = mainBlock;
        newBlock->prev = NULL;
        mainBlock->prev = newBlock;

        totalBlocks++;                          //increment count of used blocks

        printf("Memory allocated. Bytes left = %d\n", mainBlock->size);
        printf("Total blocks = %d\n", totalBlocks);

        front = newBlock;

        return newBlock;
    }
    //return NULL;
}
void my_free(void *block) {
    Block *freeBlock = block;
    int flag = FALSE;

    freeBlock->free = TRUE;

    if (freeBlock->prev->free) {
        freeBlock->prev->size += freeBlock->size;
        freeBlock->prev->next = freeBlock->next;
        freeBlock->next->prev = freeBlock->prev;
        flag = TRUE;
    }
    if (freeBlock->next->free) {
        if (flag) {
            freeBlock->prev->size += freeBlock->next->size;
            freeBlock->prev->next = freeBlock->next->next;
            freeBlock->next->next->prev = freeBlock->prev;
        } else {
            freeBlock->size += freeBlock->next->size;
            freeBlock->next = freeBlock->next->next;
            freeBlock->next->prev = freeBlock;
        }
    }
}
