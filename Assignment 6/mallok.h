/*
 * Duy Huynh
 * TCSS 333 - Spring '15
 * Assignment 6
 * mallok.h
 *
 * Header file for mallok.c, my private heap
 * memory management functions. Includes
 * functions for allocating memory and freeing
 * memory of a private heap managed by me.
 *
 */

#ifndef MALLOK_H_
#define MALLOK_H_

void create_pool(int size);
void *my_malloc(int size);
void my_free(void *block);
void printBlocks();

typedef enum {
    FALSE, TRUE
} Bool;

struct block {
    void *startAddress;
    int size;
    Bool free;
    struct block *next;
};

typedef struct block Block;

#endif /* MALLOK_H_ */
