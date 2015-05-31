/*
 * Duy Huynh
 * TCSS 333 - Spring '15
 * Assignment 6
 * mallok_test.c
 *
 * Main application that tests my personal private heap
 * and memory management (mallok.c, mallok.h). Performs
 * several tests on mallok.c, requesting, using and
 * freeing bytes from my private heap.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mallok.h"

void test1();
void test2();
void test3();
void test4();
void test5();

// Main
int main(void) {

    test1();
    test2();
    test3();
    test4();
    test5();

    return 0;
}

// Test 1
void test1() {
    /* Test 1
     * ------
     *     1. Create pool of 1000 bytes
     *     2. Count number of successful requests for 10-byte blocks
     */
    printf("Test 1: Pool 1000, request blocks of 10\n");
    printf("---------------------------------------------------\n");
    create_pool(1000);
    int successCount = 0;
    while (my_malloc(250) != NULL) {
        successCount++;
    }
    printf("Successfully allocated blocks of size 250, %d times\n",
            successCount);
    printf("===================================================\n\n");
}

// Test2
void test2() {
    /* Test 2
     * ------
     *     1. Create pool of 1000 bytes
     *     2. Request 5x 200-byte blocks
     *     3. Free all 5 blocks
     *     4. Repeat 2-3
     */
    printf("Test 2: Pool 1000, request 5 200-byte blocks, free all, repeat\n");
    printf("---------------------------------------------------\n");
    create_pool(1000);
    int i;
    // Request 5 blocks of size 200:
    for (i = 0; i < 5; i++) {
        char *one = my_malloc(200);
        char *two = my_malloc(200);
        char *three = my_malloc(200);
        char *four = my_malloc(200);
        char *five = my_malloc(200);

        printf("\n");
        printBlocks();
        printf("\n");

        my_free(one);
        my_free(two);
        my_free(three);
        my_free(four);
        my_free(five);

        printBlocks();
    }
    printf("===================================================\n\n");
}

// Test 3
void test3() {
    /* Test 3
     * ------
     *     1. Create pool of 1000 bytes
     *     2. Request 5x 200-byte blocks
     *     3. Free middle block
     *     4. Request 210-byte block (fails)
     *     5. Request 150-byte block (succeeds)
     *     6. Request 60-byte block (fails)
     *     7. Request 50-byte block (succeeds)
     */
    printf("Test 3: Pool 1000, request 5 200-byte blocks,\n");
    printf("delete middle block, request too large, then smaller blocks\n");
    printf("---------------------------------------------------\n");
    create_pool(1000);
    char *one = my_malloc(200);
    char *two = my_malloc(200);
    char *three = my_malloc(200);
    char *four = my_malloc(200);
    char *five = my_malloc(200);

    my_free(three);
    char *six = my_malloc(210);
    six = my_malloc(150);
    six = my_malloc(60);
    six = my_malloc(50);
    printf("===================================================\n\n");
}

// Test 4
void test4() {
    /* Test 4
     * ------
     *     1. Create pool of 1000 bytes
     *     2. Request 5x 200-byte blocks
     *     3. Fill first block with letter 'A'
     *     4. Fill second with 'B's, etc...
     *     5. Verify letters are there
     */
    printf("Test 4: Pool 1000, request 5 200-byte blocks,\n");
    printf("Fill first block with 'A', second with 'B', etc and verify.\n");
    printf("---------------------------------------------------\n");
    create_pool(1000);
    char *A = my_malloc(200);
    char *B = my_malloc(200);
    char *C = my_malloc(200);
    char *D = my_malloc(200);
    char *E = my_malloc(200);

    memset(A, 'A', 200);
    memset(B, 'B', 200);
    memset(C, 'C', 200);
    memset(D, 'D', 200);
    memset(E, 'E', 200);

    // Print out A's
    int i = 0;
    for (i = 0; i < 200; i++) {
        printf("%c", A[i]);
    }
    printf("\n");

    // Print out B's
    i = 0;
    for (i = 0; i < 200; i++) {
        printf("%c", B[i]);
    }
    printf("\n");

    // Print out C's
    i = 0;
    for (i = 0; i < 200; i++) {
        printf("%c", C[i]);
    }
    printf("\n");

    // Print out D's
    i = 0;
    for (i = 0; i < 200; i++) {
        printf("%c", D[i]);
    }
    printf("\n");

    // Print out D's
    i = 0;
    for (i = 0; i < 200; i++) {
        printf("%c", E[i]);
    }
    printf("\n");

    printf("===================================================\n\n");

}

// Test 5
void test5() {
    /* Test 5
     * ------
     *     1. Create pool of 1000 bytes
     *     2. Request and return block of 1000 bytes.
     *     3. Request and return block of 250 bytes.
     *     4. Request and return block of 100 bytes.
     */
    printf("Test 5: Pool 1000, request and return block of 1000 bytes,\n");
    printf("then 250 bytes, then 100 bytes.\n");
    printf("---------------------------------------------------\n");
    create_pool(1000);
    char *test = my_malloc(1000);
    my_free(test);
    test = my_malloc(250);
    my_free(test);
    test = my_malloc(100);
    my_free(test);

    printf("===================================================\n\n");
}

