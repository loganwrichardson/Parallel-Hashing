//
// Created by Logan Richardson on 7/20/23.
//
//#ifndef COMPREHENSIVE_VIDHI_AND_LOGAN_HASING_H
//#define COMPREHENSIVE_VIDHI_AND_LOGAN_HASING_H

#ifndef HASHING_H
#define HASHING_H
#include "linked_list.h"

typedef struct HashTable_t {
    LinkedList **table;
    int capacity;
} HashTable;

// Function Declarations
HashTable* hash_table_create(int capacity);
void ht_destroy(HashTable *ht);
int hash_func(int key);
void hash_table_insert(HashTable *ht, int data);
void hash_table_remove(HashTable *ht, int data);
void hash_table_print(HashTable *ht);

#endif
//#endif //COMPREHENSIVE_VIDHI_AND_LOGAN_HASING_H
