/*
 * Duy Huynh
 * TCSS 333 - Spring '15
 * Assignment 6
 * mallok.c
 *
 * Implementation of my personal private
 * heap memory management. Has functions to
 * allocate and set aside memory for use and
 * also to free blocks of memory.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "mallok.h"

// Private heap
static Block *privateHeap;
static Block *headBlock;

// Allocate a main block of memory to be used.
void create_pool(int size) {

    // Allocate space for private heap
    privateHeap = malloc(sizeof(Block));

    // Set up private heap
    privateHeap->startAddress = malloc(size);
    privateHeap->size = size; // Always holds remaining size
    privateHeap->free = TRUE; // Whether entire block free
    privateHeap->next = NULL;
    printf("Finished creating pool of size %d\n", size);

    headBlock = NULL;

}

// Allocate a block of memory, if possible, given a size.
void *my_malloc(int size) {

    // Special case 0?
    if (size == 0) {
        printf("Error: Request size can't be 0\n");
        return NULL;
    }

    // first block:
    if (headBlock == NULL) {
        if (size <= privateHeap->size) {
            headBlock = malloc(sizeof(Block));
            headBlock->size = size;
            headBlock->free = FALSE;
            headBlock->startAddress = privateHeap->startAddress;
            headBlock->next = privateHeap;

            privateHeap->size -= size;
            privateHeap->startAddress += size;
            //printf("Allocated %d (for head)\n", size);
            printf("Successfully allocated %d\n", size);
            return headBlock->startAddress;
        }
    }
    // Check every single block for size availability and if free
    Block *current = headBlock;
    while (current != NULL) {

        // check the size:
        if (size <= current->size) {
            if (current->free) {
                // Divvy up free block and set aside remaining bytes
                Block *newBlock = malloc(sizeof(Block));
                newBlock->free = TRUE;
                newBlock->startAddress = current->startAddress + size;
                newBlock->size = current->size - size;
                newBlock->next = current->next;

                // Update this block as used, given the size
                current->next = newBlock;
                current->size = size;
                current->free = FALSE;
                printf("Successfully allocated %d\n", current->size);
                return current->startAddress;
            }
        }
        current = current->next;

    }
    printf("Unable to allocate requested block of size %d\n", size);
    return NULL;
}

// If possible, free up allocated memory.
void my_free(void *block) {

    Block *freeBlock = (Block*) block;
    Block*current = headBlock;

    int freedBlockIndex = 0;
    Bool isValidBlock = FALSE;
    // Find the block and then free it
    while (current != NULL) {
        if (current->startAddress == freeBlock) {
            isValidBlock = TRUE;
            current->free = TRUE;
            //printf("Successfully freed this block!\n");
            printf("Successfully freed block of %d bytes!\n", current->size);
            break;
        } else {
            current = current->next;
            freedBlockIndex++;
        }
    }

    // Check for any neighboring free blocks, only if passed block exists:
    if (isValidBlock) {
        // Merge any existing free block that comes after this block:
        if (current->next->free) {
            current->size += current->next->size;
            current->next = current->next->next;
            //printf("Merged existing free block that came after!\n");
        }

        // Merge any exisisting free block that comes previous this block:
        if (current != headBlock) {
            current = headBlock;
            int i = 0;
            for (i = 0; i < freedBlockIndex - 1; i++) {
                current = current->next;
            }
            if (current->free) {
                current->size += current->next->size;
                current->next = current->next->next;
                // printf("Merged existing free block that came previous!\n");
            }
        }

    }

}

// For debugging, print out the blocks currently in use
void printBlocks() {

    printf("Current heap state:\n");
    Block*current = headBlock;
    int i = 0; // Block count

    // The case when no blocks are in use:
    if (current->next == NULL) {
        printf("Empty heap @%p, size %d, free %d, startAdd %p, next %p\n",
                current, current->size, current->free, current->startAddress,
                current->next);
    }

    // When the heap is in use, print out the blocks:
    while (current->next != NULL) {
        printf("%dth block @%p, size %d, free %d, startAdd %p, next %p\n", i,
                current, current->size, current->free, current->startAddress,
                current->next);
        current = current->next;
        i++;
    }

}

