//  create a pool of 1000 bytes. Count how times you can successfully request a block of size 10

//create a pool of 1000 bytes. Make 5 requests for blocks of 200 bytes.
// Free all 5 blocks.  Repeat this request/free pattern several times
// to make sure you can reuse blocks after they are returned.

#include <stdio.h>
#include <stdlib.h>
#include "mallok.h"

int main(void) {

    // create pool of 1000 bytes, then count successful size-10
    create_pool(1000);
    int allocations = 1000 / 10;
    int i;
    for (i = 0; i < allocations; i++) {
        printf("Allocated 10 bytes\n");
        my_malloc(10);
    }

}
