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
int max = 1000;

// Function Declarations
void init_hash_table();
int hash_func(int key);
struct node* get_element(struct node *list, int find_index);
void insert(int key, int value);
void rehash();
void remove_node(int key);
int find(int key, struct node *list);

/**
 * Initialize the hash table
 */
void init_hash_table() {
    int k = 0;
    for (k = 0; k < max; k++) {
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
    double n;
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
//    //TODO: refactor this
//    //TODO: consider -- maybe we don't need this functionality
//    n = (1.0 * size) / max;
//    if (n >= 0.75) {
//        // rehashing
//        rehash();
//    }
}

void rehash() {
    struct hash_table_item *temp = hash_table;
    /** temp pointing to the current Hash Table array */

    int i = 0, n = max;
    size = 0;
    max = 2 * max;

    /**
     *array variable is assigned with newly created Hash Table
     *with double of previous array size
    */

    hash_table = (struct hash_table_item*) malloc(max * sizeof(struct node));
    init_hash_table();

    for (i = 0; i < n; i++) {
        /* Extracting the Linked List at position i of Hash Table array */

        struct node* list = (struct node*) temp[i].head;
        if (list == NULL) {
            /* if there is no Linked List, then continue */

            continue;
        }
        else {
            /**
             *Presence of Linked List at i
             *Keep moving and accessing the Linked List item until the end.
             *Get one key and value at a time and add it to new Hash Table array.
            */

            while (list != NULL) {
                insert(list->key, list->value);
                list = list->next;
            }
        }
    }
    temp = NULL;
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
    int i = 0;
    for (i=0; i < max; i++) {
        struct node *temp = hash_table[i].head;
        if (temp == NULL) {
            printf("hash_table[%d] has not elements\n", i);
        }
        else {
            printf("hash_table[%d] has elements: ", i);
            while (temp != NULL) {
                printf("key = %d value =%d\t", temp->key, temp->value);
                temp = temp->next;
            }
            printf("\n");
        }
    }

}

int main() {
    int choice, key, value, n, c;

    key = 10;
    value = 20;
    hash_table = (struct hash_table_item*) malloc(max * sizeof(struct hash_table_item*));
    init_hash_table();
    int i = 0;
    for (i=0; i < 100; i++) {
        key++;
        value++;
        insert(key, value);
    }
    display();
}



