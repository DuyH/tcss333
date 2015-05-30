/*
 * mallok.h
 *
 *  Created on: May 27, 2015
 *      Author: Duy
 */

#ifndef MALLOK_H_
#define MALLOK_H_

void create_pool(int size);
void *my_malloc(int size);
void my_free(void *block);

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
