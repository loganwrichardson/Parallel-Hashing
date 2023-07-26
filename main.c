//
// Created by Logan Richardson on 7/25/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "hashing.h"
#include "linked_list.h"

void test_hash_table();
void test_linked_list();
static void make_input(int * nums, int size);
#define SIZE_DEFAULT 10000

/*
 * makeInput
 * Randomly generates size numbers within the range
 * 0 and (size * 2)-1 [inclusive]. Fills the nums array
 * with those values.
 */
void make_input(int * nums, int size)
{
    int used[size << 1];
    int i, j;
    int newNum;

    for (i = 0; i < (size << 1); i++) used[i] = 0;

    j = 0;
    while (j < size)
    {
        newNum = random() % (size << 1);
        if (used[newNum] == 0)
        {
            nums[j] = newNum;
            used[newNum] = 1;
            j++;
        }
    }
}

void test_hash_table() {
    int i;
    HashTable *ht = hash_table_create(1000);

    // Ordered input 1 to 10,000
    // for (i=0; i<10000; i++) {
    //      hash_table_insert(ht, i);
    // }

    // Random input using make_input()
    size_t size = SIZE_DEFAULT;
    int * input = malloc(sizeof(int) * size);
    make_input(input, size);
    for (i=0; i < size; i++) {
       hash_table_insert(ht, input[i]);
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
    printf("Testing Linked List\n");
    test_linked_list();
    printf("\nTesting Hash Table\n");
    test_hash_table();

    return EXIT_SUCCESS;
}
