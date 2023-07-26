//
// Created by Logan Richardson on 7/25/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

Node* node_create(int data, Node *next) {
    Node *n = calloc(1, sizeof *n);
    n->data = data;
    n->next = next;
    return n;
}

void node_destroy(Node *node) {
    free(node);
    return;
}

LinkedList* linked_list_create() {
    LinkedList *list = calloc(1, sizeof *list);
    list->head = NULL;
    list->size = 0;
    return list;
}

void linked_list_destroy(LinkedList *list) {
    return;
}

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