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
 * Node structure for storing each data point
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
 * Used for the outer level hash table as well as node chaining
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
node_t create_node(int key, int data);
void init_hash_table();
int hash_func(int key);
void insert(int key, int data);
void remove(int key);
int find(int key, linked_list hash_table);

/**
 * Creates a node for insertion into the hash table
 * @param key: int
 * @param value: int
 * @return node_t
 */
node_t create_node(int key, int data) {
    node * temp = (struct node *) malloc(sizeOf(struct node));
    temp->key = key;
    temp->value = data;
    temp->next = NULL;
    return temp;
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
 * @param data: struct node_t
 */
void insert(int key, int data) {
    // Keeps track of if you need to rehash
    float n = 0.0;
    // Find the hash index.
    int hash_index = hash_func(key);
    // Store the linked list from the hash table index
    linked_list list = (struct node *) hash_table[hash_index].head;

    node * temp = create_node(key, data);

    if (list == NULL) {
        // No linked list is present at the node.
        hash_table[hash_index].head = temp;
        hash_table[hash_index].tail = temp;
        size++;
    }
    else {
        // There is a linked list present at the hash table node
        int find_index = find(key,*list);
        if (find_index == -1) {
            // The key is not already present in the chaining linked list
            hash_table[hash_index].tail->next = temp;
            hash_table[hash_index].tail = temp;
            size + ;
        }
        else {
            // There is a linked list at the hashed node
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
 * Remove
 * Removes an entry from the hash table.
 * @param value: struct node_t
 */
void remove(int key) {
    // Hash the key
    int hash_index = hash_func(key);
    // Copy the linked list at the hash table index
    linked_list list = (struct node*) hash_table[hash_index].head;

    if (list == NULL) {
        // There is no linked list at the hash table index.
        printf("The node indexed by the key: %d does not exist in the hash table.\n", key);
    }
    else {
        /**
         * There is a linked list at the hash table index.
         * Search the linked list for the node.
         */
        int find_index = find(key, list);
        if (find_index == -1) {
            // The key is not present in the linked list.
            printf("The node indexed by the key: %d does not exist in the hash table.\n", key);
        }
        else {
            // The key is present in the linked list.
            node temp = list;
            if (temp->key == key) {
                // Remove the node from the chaining list.
                hash_table[hash_index].head = temp->next;
                // Free the memory space used by temp
                free(temp);
                printf("The node indexed by the key: %d has been removed.\n", key);
                return;
            }

            while (temp->next->key != key) {
                //Scan through the linked list while checking the key of next node
                temp = temp->next;
            }

            if (hash_table[hash_index]).tail = temp->next) {
                // Remove the node by setting temp->next to null
                temp->next = NULL;
                hash_table[hash_index].tail = temp;
            }
            else {
                //TODO: check to make sure this is really eliminating the node from the hash table
                temp->next = temp->next->next;
            }
            //TODO: Might need to free temp here
            //free(temp)
            printf("The node indexed by the key: %d has been removed.\n", key);
        }
    }
}

/**
 * Find the value according to key in the hash table.
 * @param key: int
 * @param hash_table: struct linked_list_t
 * Returns -1 if the key is not found, otherwise returns the value associated with the key.
 */
int find(int key, linked_list hash_table) {
        int hash_index = hash_func(key);

        //TODO: refactor the hash_table->entries
        node current = hash_table->entries[hash_index];

        while(current != NULL){
            if (current->key == key){
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



