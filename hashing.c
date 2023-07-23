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
#include "hashing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Number of values to insert
#define NUM_NODES 1000
// Size of the hash table: NUM_NODES squared
#define HASH_TABLE_SIZE (NUM_NODES * NUM_NODES)

/**
 * Node structure for storing each data point
 * key: the hash key for the data point
 * value: the data to be stored
 * node * next: next node for the linked list, null if not needed
 */
struct node {
    int key;
    int value;
    struct node *next;
};

/**
 * Structure for creating a linked list
 * Used for the outer level hash table as well as node chaining
 */
struct hash_table_item {
    // The head of the linked list
    struct node *head;
    // The tail of the linked list
    struct node *tail;
};

// Hash Table
struct hash_table_item *hash_table;
// Number of nodes in the hash table
int size = 0;
// Maximum size of the chaining (collision resolution) array
int max = 10;

// Function Declarations
void init_hash_table();
int hash_func(int key);
void insert(int key, int data);
void remove_node(int key);
int find(int key, struct node *list);

/**
 * Creates a node for insertion into the hash table
 * @param key: int
 * @param value: int
 * @return node_t
 */
//struct node_t * create_node(int key, int data) {
//    struct node_t *temp = malloc(sizeof(struct node_t));
//    temp->key = key;
//    temp->value = data;
//    temp->next = NULL;
//    return temp;
//}

/**
 * Initialize the hash table
 */
void init_hash_table() {
    int k = 0;
    for (k = 0; k < HASH_TABLE_SIZE; k++) {
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
    return (int)((2971 * key + 101923) % 128189) % HASH_TABLE_SIZE;
}

struct node* get_element(struct node *list, int find_index) {
    int i = 0;
    struct node *temp = list;
    while (i != find_index) {
        temp = temp->next;
        i++;
    }
    return temp;
}

/**
 * Insert
 * Inserts an entry into the hash table.
 * @param key: int
 * @param data: struct node_t
 */
void insert(int key, int value) {
    // Keeps track of if you need to rehash
    float n = 0.0;
    // Find the hash index.
    int hash_index = hash_func(key);
    // Store the linked list from the hash table index
    struct node *list = (struct node*) hash_table[hash_index].head;

    struct node *item = (struct node*) malloc(sizeof(struct node));
    item->key = key;
    item->value = value;
    item->next = NULL;

    if (list == NULL) {
        // No linked list is present at the node.
        hash_table[hash_index].head = item;
        hash_table[hash_index].tail = item;
        size++;
    }
    else {
        // There is a linked list present at the hash table node
        int find_index = find(key, list);
        if (find_index == -1) {
            // The key is not already present in the chaining linked list
            hash_table[hash_index].tail->next = item;
            hash_table[hash_index].tail = item;
            size ++;
        }
        else {
            // There is a linked list at the hashed node
            // Update the value of the existing key
            //TODO: consider ... is this the best thing to do here?
            //TODO: will this just overwrite the existing node?
            struct node *element = get_element(list, find_index);
            element->value = value;
        }
    }
    //TODO: refactor this
    //TODO: consider -- maybe we don't need this functionality
//    n = (1.0 * size) / max;
//    if (n >= 0.75) {
//        // rehashing
//        rehash();
//    }
}

/**
 * Remove
 * Removes an entry from the hash table.
 * @param value: struct node_t
 */
void remove_node(int key) {
    // Hash the key
    int hash_index = hash_func(key);
    // Copy the linked list at the hash table index
    struct node *list = (struct node*) hash_table[hash_index].head;

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
            struct node *temp = list;
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

            if (hash_table[hash_index].tail == temp->next) {
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
 * Find the node according to the key in the hash table.
 * @param key: int
 * @param hash_table: struct linked_list_t
 * Returns -1 if the key is not found, otherwise returns the value associated with the key.
 */
int find(int key, struct node* list) {
        int hash_index = hash_func(key);

        int retval = 0;
        //TODO: refactor the hash_table->entries
        struct node *temp = list;

        while(temp != NULL){
            if (temp->key == key){
                return retval;
            }
            temp = temp->next;
            retval++;
        }
        return -1; // Key not found//
}

void display() {

}

void main() {
    int key = 10;
    int data = 500;

}



