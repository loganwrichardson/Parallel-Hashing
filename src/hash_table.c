/**
 * Created by Logan Richardson and Vidhi Patel
 * @version 1.0
 * @date 7/20/23
 *
 * This program hashes data using a universal hashing algorithm
 * and resolves collisions with linked list chaining.
 */

#include "helpers.h"
#include "macros.h"
#include "wrappers.h"
#include "producerConsumer1.h"
#include "producerConsumer2.h"
#include "hash_table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Creates the hash table.
 * @param numBuckets: int
 * @return HashTable_t
 */
HashTable* hash_table_create(int numBuckets) {
    int i;

    // Creates the hash table in memory
    HashTable *ht = calloc(1, sizeof *ht);
    // Sets the hash table capacity
    ht->numBuckets = numBuckets;
    // allocates memory for the number of linked lists
    ht->table = calloc(ht->numBuckets, sizeof *(ht->table));
    // allocate memory for each linked list in the array

    for(i=0; i < ht->numBuckets; i++){
        ht->table[i] = linked_list_create();
    }

    // return the pointer to the array of empty linked lists
    return ht;
}

/**
 * Universal Hash Function.
 * h(k) = ((ak + b) mod p) mod m (p is prime or relatively prime with m;
 * @param key: int
 * @return int
 */
int hash_func(HashTable *ht, int key) {
    return (int)((2971 * key + 101923) % 128189) % ht->numBuckets;
}

/**
 * Inserts a node into the Hash Table.
 * @param ht: HashTable_t
 * @param data: int
 */
void hash_table_insert(HashTable * ht, int data) {
    // Get the hash key
    int key = hash_func(ht, data);
    // Insert the data
    linked_list_in_order_insert(ht->table[key], data);
    return;
}

/**
 * Inserts into the hash table using node locks.
 * @param ht: HashTable_t
 * @param data: int
 */
void hash_table_insert_with_node_locks(HashTable * ht, int data) {
    // Get the hash key
    int key = hash_func(ht, data);
    // Insert the data
    linked_list_in_order_insert_with_hand_over_hand_locking(ht->table[key], data);
    return;
}


/**
 * Insert into the Hash Table using compare and swap.
 * @param ht: HashTable_t
 * @param data: int
 */
void hash_table_insert_with_cas(HashTable * ht, int data) {
    // Get the hash key
    int key = hash_func(ht, data);
    // Insert the data
    linked_list_in_order_insert_with_cas(ht->table[key], data);
    return;
}

/**
 * Removes a value from the Hash Table.
 * @param ht: HashTable_t
 * @param data: int
 */
void hash_table_remove(HashTable *ht, int data) {
    int key = hash_func(ht, data);
    linked_list_remove(ht->table[key], data);
}

/**
 * Prints the Hash Table.
 * @param ht: HashTable_t
 */
void hash_table_print(HashTable *ht) {
    int i;

    for(i = 0; i < ht->numBuckets; i++) {
        linked_list_print(ht->table[i]);
    }
    return;
}

/**
 * Get the numbers from the hash table in order.
 * @param ht: HashTable_t
 * @param array: int *
 */
void HSTGetNums(HashTable * ht, int * array)
{
    inorder_ht(ht, array);
}

/**
 * Traverses the hash table in order.
 * @param ht: HashTable_t
 * @param array: int *
 */
void inorder_ht(HashTable * ht, int * array) {
   if (ht == NULL) {
       return;
   }
   int i = 0;
   int j = 0;
   LinkedList *cur_list = ht->table[j];
   Node *cur_node = cur_list->head;
   while(j < ht->numBuckets) {
        // Iterates lists (buckets)
        while (cur_node != NULL) {
            // Iterates nodes
            array[i] = cur_node->data;
            cur_node = cur_node->next;
            i++;
        }
        j++;
        if (j < ht->numBuckets) {
            cur_list = ht->table[j];
        }
        if (cur_list != NULL) {
            cur_node = cur_list->head;
        }
    }
}

/**
 * Creates the args to pass into the hash table.
 * @param ht: HashTable_t
 * @param whichPtr: int
 * @return Args*
 */
Args* args_create(HashTable * ht, int whichPtr) {
    Args * args = calloc(1, sizeof(Args));
    args->whichPtr = whichPtr;
    args->ht = ht;
    return args;
}