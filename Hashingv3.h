//
// Created by Logan Richardson on 7/20/23.
//

#ifndef HASHING_H3
#define HASHING_H3
#include <pthread.h>
#include "linked_list.h"

typedef struct HashTable3_t {
    LinkedList **table;
    int capacity;
} HTv3;

// Function Declarations
HTv3 * hash_table_create3(int capacity);
void ht_destroy(HTv3 *ht3);
int hash_func3(HTv3 *ht3, int key);
void hash_table_insert3(HTv3 *ht3, int data);
void hash_table_remove3(HTv3 *ht3, int data);
void hash_table_print3(HTv3 *ht3);
double doHTv3(int * sortedInput, int size, int numThreads, int which);

#endif