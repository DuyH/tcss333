/*
 x` * mallok.c
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
static int sizeLeft;

void create_pool(int size) {

    // Allocate space for private heap
    wholeBlock = malloc(size);
    headBlock = wholeBlock; // set address of starting
    sizeLeft = size;

    // Set up head block
    headBlock->startAddress = wholeBlock;
    headBlock->free = TRUE;
    headBlock->next = NULL;
    headBlock->size = 0;

    // Set up initial block
    wholeBlock->startAddress = wholeBlock;
    wholeBlock->size = size; // Always holds total size
    wholeBlock->free = TRUE; // Whether entire block free
    wholeBlock->next = NULL;
    printf("Finished creating pool");

}
void *my_malloc(int size) {

    // Requested size is larger than private heap:
    if (sizeLeft < size) {
        return NULL;
    }

    // If nothing in private heap yet, then init head with size
    if (headBlock->size == 0) {
        headBlock->size = size;
        sizeLeft -= size;
        headBlock->free = FALSE;
        Block *newBlock = malloc(sizeof(Block));
        newBlock->startAddress = headBlock->startAddress + size;
        newBlock->size = sizeLeft;
        newBlock->free = TRUE;
        newBlock->next = NULL;
        headBlock->next = newBlock;
    } else {
        // Start with
        Block *ptr = headBlock->next;
        int sizeCounter = headBlock->size;

        // Point to next free block
        while (!ptr->free) {
            ptr = ptr->next;
            sizeLeft -= ptr->size;
            sizeCounter = +ptr->size;
        }

        // We are at free block now
        // Check if request size smaller than size that's left
        if (sizeLeft >= size) {

            //THIS BLOCK IS FREE AND CAN ACCOMODATE SIZE:
            ptr->size = size;
            sizeCounter += size;
            sizeLeft -= size;
            ptr->free = FALSE;

            // Now assign next free space
            Block *newBlock = malloc(sizeof(Block));
            // Create new block
            ptr->next = newBlock;
            newBlock->startAddress = ptr->startAddress + size;
            newBlock->size = sizeLeft;
            newBlock->free = TRUE;
            newBlock->next = NULL;
        }
    }

}
void my_free(void *block) {

    // Cast the block
    Block *blockToFree = block;

    // Is "block" valid? Check its address with addresses in heap
    Bool isValidBlock = FALSE;
    int prevBlockIndex = 0;
    Block *ptr = headBlock;
    while (ptr != NULL) {
        if (ptr->startAddress == blockToFree->startAddress) {
            isValidBlock = TRUE;
            break;
        }
        prevBlockIndex++;
        ptr = ptr->next;
    }

    // We DO have a valid block, so work on it:

    if (isValidBlock) {

        // Indicate this block is free
        blockToFree->free = TRUE;

        // Merge any existing free block that comes after this block:
        Block *nextBlock = blockToFree->next;
        if (nextBlock->free) {
            // If next block free:
            // 1. Include the next block's freed size to this block
            // 2. Redirect this block's next to next block's next
            blockToFree->next = nextBlock->next;
            blockToFree->size += nextBlock->size;
        }

        // Merge any existing free block that comes before this block:
        ptr = headBlock;
        int i;
        for (i = 0; i < prevBlockIndex; i++) {
            ptr = ptr->next;
        }

        // Now we're at previous block, check is it free?
        if (ptr->free) {
            // Prev block is free too so:
            // 1. Update its size to include this block
            // 2. Redirect prev block's next to next of the freed
            ptr->next = blockToFree->next;
            ptr->size += blockToFree->size;
        }

    }

}
