// Created by Logan Richardson and Vidhi Patel on 7/20/23.

#include "linked_list.h"

/**
 * Structure for the Hash Table
 * table: LinkedList ** - Pointer to the table
 * numBuckets: int - Number of buckets in the Hash Table
 */
typedef struct HashTable_t {
    LinkedList **table;
    int numBuckets;
} HashTable;

/**
 * Structure for the arguments which are passed to the threads as a void pointer
 * whichPtr: int - Selects producer 1 / producer 2
 * ht: HashTable_t * - Pointer to the Hash Table
 */
typedef struct args_t {
    int whichPtr;
    HashTable * ht;
} Args;

// Functions used by the hash table
HashTable* hash_table_create(int numBuckets);

void ht_destroy(HashTable *ht);

int hash_func(HashTable *ht, int key);

void hash_table_insert(HashTable *ht, int data);

void hash_table_insert_with_node_locks(HashTable *ht, int data);

void hash_table_insert_with_cas(HashTable * ht, int data);

void hash_table_remove(HashTable *ht, int data);

void hash_table_print(HashTable *ht);

void HSTGetNums(HashTable * ht, int * array);

void inorder_ht(HashTable * ht, int * array);

Args* args_create(HashTable * ht, int whichPtr);

void runHashingWithProducerConsumer1(int * input, int * sortedInput, int numBuckets, int numNodes,
                                     int numConsume, int numProduce, int which);

void runHashingWithProducerConsumer2(int * input, int * sortedInput, int numBuckets, int numNodes,
                                     int numConsume, int numProduce, int which);

