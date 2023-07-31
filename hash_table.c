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
#include "BSTversions.h"
#include "hash_table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

HashTable* hash_table_create(int capacity) {
    int i;

    // Creates the hash table in memory
    HashTable *ht = calloc(1, sizeof *ht);
    // Sets the hash table capacity
    ht->capacity = capacity;
    // allocates memory for the number of linked lists
    ht->table = calloc(ht->capacity, sizeof *(ht->table));
    // allocate memory for each linked list in the array

    for(i=0; i < ht->capacity; i++){
        ht->table[i] = linked_list_create();
    }

    // return the pointer to the array of empty linked lists
    return ht;
}

/**
 * Universal Hash Function
 * h(k) = ((ak + b) mod p) mod m (p is prime or relatively prime with m;
 * @param key: int
 * @return int
 */
int hash_func(HashTable *ht, int key) {
    return (int)((2971 * key + 101923) % 128189) % ht->capacity;
}

void hash_table_insert(HashTable * ht, int data) {
    // Get the hash key
    int key = hash_func(ht, data);
    // Insert the data
    linked_list_in_order_insert(ht->table[key], data);
    return;
}

void hash_table_remove(HashTable *ht, int data) {
    int key = hash_func(ht, data);
    linked_list_remove(ht->table[key], data);
}

void hash_table_print(HashTable *ht) {
    int i;

    for(i = 0; i < ht->capacity; i++) {
        linked_list_print(ht->table[i]);
    }
    return;
}



