//
// Created by Logan Richardson on 7/25/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"

void test_hash_table();
void test_linked_list();
static void make_input(int * nums, int size);
static void sortInput(int * nums, int size);
static void getArgs(int argc, char * argv[], int * size,
                    int * numConsume, int * numProduce);
static void printUsage();

//default hash table size and default number of threads
#define SIZE_DEFAULT 10000
#define NUMCONSUME_DEFAULT 4
#define NUMPRODUCE_DEFAULT 4

void test_hash_table() {
    int i;
    HashTable *ht = hash_table_create(SIZE_DEFAULT);

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

/*
 * sortInput
 * sort the nums array using an insertion sort
 */
void sortInput(int * nums, int size)
{
    int i, j, insert;
    for (i = 1; i < size; i++)
    {
        insert = nums[i];
        for (j = i-1; j >= 0; j--)
        {
            if (nums[j] > insert)
            {
                nums[j+1] = nums[j];
                nums[j] = insert;
            }
        }
    }
}

/*
 * getArgs
 * Parse the command line arguments to get the number of values
 * to insert into the BST, the number of consumer threads, and the
 * number of producer threads.
 * argc - number of command line arguments
 * argv - array of command line arguments
 * size - pointer to int to be set to the number of values
 *        to be inserted into the BST
 * numConsume - pointer to int to be set to the number of consumer
 *        threads to get a value from the producer-consumer buffer and
 *        insert into a BST
 * numProduce - pointer to the int to be set to the number of
 *        producer threads to fill the producer-consumer buffer
 */
//
/*
 * printUsage
 * Print the usage information and exit
 */
void printUsage()
{
    printf("usage: ./bst [-s <size>] [-c <cthreads>] [-p <pthreads> ] [ -h ] \n");
    printf("       <size> is the number of nodes to insert\n");
    printf("              default: %d\n", SIZE_DEFAULT);
    printf("       <cthreads> is the number of consumer threads to use\n");
    printf("              default: %d\n", NUMCONSUME_DEFAULT);
    printf("       <threads> is the number of producer threads to use\n");
    printf("              default: %d\n", NUMPRODUCE_DEFAULT);
    printf("       -h print usage info and exit\n");
    exit(1);
}


int main(int argc, char *argv[]) {
    printf("Testing Linked List\n");
    test_linked_list();
    printf("\nTesting Hash Table\n");
    test_hash_table();

    return EXIT_SUCCESS;
}
