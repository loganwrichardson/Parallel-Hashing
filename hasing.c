//
// Created by Logan Richardson and Vidhi Patel on 7/20/23.
//

#include "helpers.h"
#include "macros.h"
#include "wrappers.h"
#include "producerConsumer1.h"
#include "produceConsumer2.h"
#include "BSTversions.h"
#include "hasing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE_DEFAULT 1000;
int hash_table_size = SIZE_DEFAULT * SIZE_DEFAULT

struct Data {
    int val;
    int key;
};

typedef struct {
    HashEntry entries[HASH_TABLE_SIZE]
} HashTable;

static void insert(int key);
static void remove(int key);
static void find(int key, int * HashTable);

/**
 * h(k) = ((ak + b) mod p) mod m (p is prime or relatively prime with m; Universal
 * Hash Function.
 * @param key: int
 * @return int
 */
int hashFunc(int key) {
    return (int)((2971 * key + 101923) % 128189) % hash_table_size
}

struct Data * find(int key) {
    int hashIndex = hashFunct(key);

    while(HashTable->entries[hashIndex] != NULL) {
        if(hashArray[hashIndex]->key == key)
            return hashAr
    }
}

/**
 * Insert.
 * Inserts an entry into the hash table.
 * @param key: int
 * @param data: struct
 */
void insert(int key, int data) {

    struct Data *item
}

// Insert an element into the hash table using linear probing for collisions.
void insertHashTable(HashTable* table, int key, int val) {
    int index = hashFunc(key);

    while (table->entries[index].key != -1) {
        index = (index + 1) % HASH_TABLE_SIZE; // Linear probing
    }

    table->entries[index].key = key;
    table->entries[index].value = value;
}

/**
 * To initiaze the hash table
 */
void initHashTable(HashTable* table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->entries[i].key = -1;
    }
}

/**
 * Remove.
 * Removes an entry from the hash table.
 * @param value: struct Data
 */
void remove(struct Data * value) {
    int key = value->key;
    int hashIndex = hashFunct(key);

}

void display() {

}

int main() {

}



