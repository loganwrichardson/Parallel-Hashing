// Created by Logan Richardson and Vidhi Patel on 7/20/23.

#include "helpers.h"
#include "macros.h"
#include "wrappers.h"
#include "producerConsumer1.h"
#include "produceConsumer2.h"
#include "BSTversions.h"
#include "hashing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Number of values to insert
#define NUM_NODES 1000

// Size of the hash table: NUM_NODES squared
int hash_table_size = NUM_NODES * NUM_NODES;

/**
 * Node for storing each data point
 * Uses linked list chaining to resolve collisions
 * key: the hash key for the data point
 * value: the data to be stored
 * node * next: next node for the linked list, null if not needed
 */
typedef struct node_t {
    int key;
    int value;
    struct node * next;
} node;

/**
 * Structure for creating a linked list
 * Uses: hash table and chaining (collision resolution)
 */
typedef struct linked_list_t {
    // The head of the linked list
    struct node * head;
    // The tail of the linked list
    struct node * tail;
} linked_list;

// Hash Table
linked_list * hash_table[hash_table_size];
// Number of nodes in the hash table
int size = 0;
// Maximum size of the chaining (collision resolution) array
int max = 10;

// Function Declarations
void insert(int key, int data);
void remove(int key);
int find(int key, linked_list hash_table);
void init_hash_table();

/**
 * Universal Hash Function
 * h(k) = ((ak + b) mod p) mod m (p is prime or relatively prime with m;
 * @param key: int
 * @return int
 */
int hash_func(int key) {
    return (int)((2971 * key + 101923) % 128189) % hash_table_size
}

/**
 * Insert
 * Inserts an entry into the hash table.
 * @param key: int
 * @param data: struct
 */
void insert(int key, int data) {

    // Keeps track of if you need to rehash
    float n = 0.0;

    // Find the hash index.
    int hash_index = hash_func(key);

    // Store the linked list from the hash table index
    linked_list list = (struct node *) array[index].head;

    node * temp = (struct node *) malloc(sizeOf(struct node));
    temp->key = key;
    temp->value = data;
    temp->next = NULL;

    if (list == NULL) {
        // No linked list is present at the node.
        hash_array[hash_index].head = temp;
        hash_array[hash_index].tail = temp;
        size++;
    }
    else {
        // There is a linked list present at the hash table node
        int find_index = find(key, *list);
        if (find_index == -1) {
            // The key is not already present in the chaining linked list
            hash_array[index].tail->next = temp;
            hash_array[index].tail = temp;
            size + ;
        } else {
            // The key is present in the chaining linked list
            // Update the value of the existing key
            //TODO: consider ... is this the best thing to do here?
            //TODO: will this just overwrite the existing node?
            node * pre_existing_node = find(find_index, list);
            pre_existing_node->value = data;
        }
    }
    //TODO: refactor this
    //TODO: consider -- maybe we don't need this functionality
    n = (1.0 * size) / max;
    if (n >= 0.75) {
        // rehashing
        rehash();
    }
}

/**
 * Initialize the hash table
 */
void init_hash_table() {
    int k = 0;
    for (k = 0; k < hash_table_size; k++) {
        hash_table[k].head = NULL;
        hash_table[k].tail = NULL;
    }
}

/**
 * Remove
 * Removes an entry from the hash table.
 * @param value: struct Data
 */
void remove(struct node * value) {
    int key = value->key;
    int hashIndex = hash_func(key);
}

//struct node * find(int key) {
//    int hashIndex = hashFunct(key);
//
//    while(HashTable->entries[hashIndex] != NULL) {
//        if(hashArray[hashIndex]->key == key)
//            return hashArray;
//    }
//}

/**
 * Find the value according to key in the hash table.
 * Returns -1 if the key is not found, otherwise returns the value associated with the key.
 */
int find(int key, linked_list hash_table) {
        int index = hash_func(key);

        //TODO: refactor the hash_table->entries
        node * current = hash_table->entries[index];

        while(current != NULL){
            if (current-> key == key){
                return current->value;
            }
            current = current->next;
        }
        return -1; // Key not found//
}

void display() {

}

int main() {

}



