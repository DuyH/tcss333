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

struct block {
    void *startAddress;
    int size;
    Bool free;
    Block next;

};

typedef struct block Block;

typedef enum {
    FALSE, TRUE
} Bool;

#endif /* MALLOK_H_ */
