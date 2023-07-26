//
// Created by Logan Richardson on 7/25/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "hashing.h"
#include "linked_list.h"

void test_hash_table();
void test_linked_list();


void test_hash_table() {
    int i;
    HashTable *ht = hash_table_create(5);

    for (i=0; i< 20; i++) {
        hash_table_insert(ht, i);
    }
    hash_table_print(ht);

    printf("\nAfter, remove 13, 12, and 19\n");
    hash_table_remove(ht, 13);
    hash_table_remove(ht, 12);
    hash_table_remove(ht, 19);

    hash_table_print(ht);
}

void test_linked_list() {
    int i;
    LinkedList *list = linked_list_create();

    for (i = 0; i < 10; i++) {
        linked_list_insert(list, i);
    }

    linked_list_print(list);
    linked_list_remove(list, 9);
    linked_list_remove(list, 4);
    linked_list_remove(list, 3);
    linked_list_remove(list, 0);

    printf("\nAfter removing 9, 4, 3, and 0\n");
    linked_list_print(list);
}

int main(int argc, char *argv[]) {
    printf("Testing Linked List");
    test_linked_list();
    printf("Testing Hash Table");
    test_hash_table();

    return EXIT_SUCCESS;
}
