//
// Created by Logan Richardson and Vidhi Patel on 7/20/23.
//
//#ifndef COMPREHENSIVE_VIDHI_AND_LOGAN_HASING_H
//#define COMPREHENSIVE_VIDHI_AND_LOGAN_HASING_H

#ifndef HASHING_H
#define HASHING_H
#define HASH_TABLE_SIZE 1000
#include "linked_list.h"

typedef struct HashTable_t {
    LinkedList **table;
    int capacity;
    pthread_mutex_t lock;
} HashTable;

typedef struct args_t {
    int whichPtr;
    HashTable * ht;
} Args;

//typedef struct HashTable_With_Locks_t {
//    LinkedList **table;
//    int capacity;
//    pthread_mutex_t lock;
//} HashTable_with_locks;

// Function Declarations
HashTable* hash_table_create(int capacity);
void ht_destroy(HashTable *ht);
int hash_func(HashTable *ht, int key);
void hash_table_insert(HashTable *ht, int data);
void hash_table_remove(HashTable *ht, int data);
void hash_table_print(HashTable *ht);
void HSTv1GetNums(HashTable * ht, int * array);
void HSTv2GetNums(HashTable * ht, int * array);
//void HSTv3GetNums(int * array);
//void HSTv4GetNums(int * array);
int cmpfc(const void* a, const void* b);
void inorder_ht(HashTable * ht, int * array);
Args* args_create(HashTable * ht, int whichPtr);

#endif
//#endif //COMPREHENSIVE_VIDHI_AND_LOGAN_HASING_H
