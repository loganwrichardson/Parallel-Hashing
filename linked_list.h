//
// Created by Logan Richardson on 7/25/23.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 * Node structure for storing each data point
 * value: the data to be stored
 * Node_t * next: next node for the linked list, null if not needed
 */
typedef struct Node_t {
    int data;
    struct Node_t *next;
} Node;

/**
 * Structure for creating a linked list
 * Used for the chaining resolution
 */
typedef struct Linked_List_t {
    // The head of the linked list
    Node *head;
    int size;
} LinkedList;

Node* node_create(int data, Node *next);
void node_destroy(Node *node);

LinkedList* linked_list_create();
void linked_list_destroy(LinkedList *list);
void linked_list_insert(LinkedList *list, int data);
void linked_list_in_order_insert(LinkedList *list, int data);
void linked_list_remove(LinkedList *list, int data);
void linked_list_print(LinkedList *list);

#endif
