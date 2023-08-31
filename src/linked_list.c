// Created by Logan Richardson and Vidhi Patel on 7/25/23.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include "linked_list.h"

/**
 * Creates a node.
 * @param data: int
 * @param next: Node_t
 * @return Node_t
 */
Node* node_create(int data, Node *next) {
    Node *n = calloc(1, sizeof *n);
    n->data = data;
    n->next = next;
    pthread_mutex_init(&(n->lock), NULL);
    return n;
}

/**
 * Free the memory allocated for the node.
 * @param node: Node_t
 */
void node_destroy(Node *node) {
    free(node);
    return;
}

/**
 * Creates the linked list.
 * @return Linked List
 */
LinkedList* linked_list_create() {
    LinkedList *list = calloc(1, sizeof *list);
    list->head = NULL;
    list->size = 0;
    pthread_mutex_init(&(list->lock), NULL);
    return list;
}

/**
 * Destroys the linked list.
 * @param list: Linked List
 */
void linked_list_destroy(LinkedList *list) {
    return;
}

/**
 * Inserts into the linked list in order.
 * @param list: Linked List
 * @param data: int
 */
void linked_list_in_order_insert(LinkedList *list, int data) {
    Node *new_node = node_create(data, NULL);
    Node *prev = list->head;
    Node *cur_node = list->head;

    if (list->size == 0) {

        list->head = new_node;
        list->size++;
    }
    else if (new_node->data <= list->head->data) {
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
    }
    else {
        while (cur_node != NULL && new_node->data > cur_node->data) {
            prev = cur_node;
            cur_node = cur_node->next;
        }
        prev->next = new_node;
        new_node->next = cur_node;
        list->size++;
    }
    return;
}
/**
 * Inserts into the linked list using compare and swap.
 * @param list: Linked List
 * @param data: int
 */
void linked_list_in_order_insert_with_cas(LinkedList *list, int data) {
    Node *new_node = node_create(data, NULL);
    Node *prev = NULL;
    Node *cur_node = NULL;
   
    do {
        prev = NULL;
        cur_node = list->head;

        // Find the predecessor and successor nodes for the insertion
         while (cur_node != NULL && cur_node->data < data) {
             prev = cur_node;
             cur_node = cur_node->next;
         }
       
         new_node->next = cur_node;
         if (prev == NULL) {
           if (__sync_bool_compare_and_swap(&list->head, cur_node, new_node)) {
                while (true) {
                    int old_size = list->size;
                    if (__sync_bool_compare_and_swap(&list->size, old_size, old_size + 1)) {
                        return;
                    }
                }
            }
         } else {
             new_node->next = cur_node;
             if (__sync_bool_compare_and_swap(&prev->next, cur_node, new_node)) {
                 while (true) {
                     int old_size = list->size;
                     if (__sync_bool_compare_and_swap(&list->size, old_size, old_size + 1)) {
                         return;
                     }
                 }
             }
         }
    } while (1);
}

/**
 * Inserts into the linked list, in order, using hand over hand locking.
 * @param list: Linked List
 * @param data: int
 */
void linked_list_in_order_insert_with_hand_over_hand_locking(LinkedList * list, int data) {
    Node * new_node = node_create(data, NULL);
    Node * cur_node = list->head;
    pthread_mutex_lock(&list->lock);
    if (list->size == 0 || list->head->data > new_node->data) {
        // the new node inserts at the front of the list
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
        pthread_mutex_unlock(&list->lock);
        return;
    }
    // the new node does not insert at the front of the list
    // pthread_mutex_lock(&list->head->lock);
    pthread_mutex_lock(&cur_node->lock);
    pthread_mutex_unlock(&list->lock);

    while(cur_node->next != NULL && new_node->data > cur_node->next->data) {
        // scan until you find the insertion location w/ hand over hand locking
        pthread_mutex_lock(&cur_node->next->lock);
        Node * temp = cur_node;
        //pthread_mutex_unlock(&cur_node->lock);
        cur_node = cur_node->next;
        pthread_mutex_unlock(&temp->lock);
    }
    new_node->next = cur_node->next;
    cur_node->next = new_node;
    pthread_mutex_unlock(&cur_node->lock);

    // Increase the list size
    pthread_mutex_lock(&list->lock);
    list->size++;
    pthread_mutex_unlock(&list->lock);
    return;
}

/**
 * Inserts into the linked list without respect to order.
 * @param list: Linked List
 * @param data: int
 */
void linked_list_insert(LinkedList *list, int data) {
    Node *new_node = node_create(data, NULL);
    if (list->size > 0) {
        new_node->next = list->head;
    }
    else {
        new_node->next = NULL;
    }
    list->head = new_node;
    list->size++;
    return;
}

/**
 * Removes a node from the linked list.
 * @param list: Linked List
 * @param data: int
 */
void linked_list_remove(LinkedList *list, int data) {
    Node * target = list->head;
    Node * prev = list->head;

    // If the target is the head of the list
    // remove first element
    if (target->data == data) {
        list->head = list->head->next;
        node_destroy(target);
        list->size--;
        return;
    }

    // If the target is not the head of the list
    while (target->data != data) {
        prev = target;
        target = target->next;
    }

    prev->next = target->next;
    node_destroy(target);

    list->size--;
    return;
}

/**
 * Prints the Linked List
 * @param list: Linked List
 */
void linked_list_print(LinkedList *list) {
    printf("Print linked list (%d items: ", list->size);
    Node *cur_node = list->head;
    if (cur_node == NULL) {
        printf(")\n");
    } else {
        while (cur_node != NULL) {
            if (cur_node->next != NULL) {
                printf("%d, ", cur_node->data);
            } else {
                printf("%d)\n", cur_node->data);
            }
            cur_node = cur_node->next;
        }
    }
}
