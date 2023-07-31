//
// Created by Logan Richardson and Vidhi Patel on 7/27/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "helpers.h"
#include "macros.h"
#include "wrappers.h"
#include "producerConsumer1.h"
#include "producerConsumer2.h"
#include "BSTversions.h"
#include "hash_table.h"

//Build the Hash Table using just one thread (the calling thread).
//Check for correctness.
//Return the time it takes to do it.
//double doBSTv1(int * input, int * sortedInput, int size)
double doHTv1(int * sortedInput, int size, int which)
{
    int i;
    int hashValues[size];
    // Takes the place of resetBSTv1
    HashTable * temp = hash_table_create(size);


    TIMERSTART(HTv1)

    int * input = malloc(sizeof(int) * size);
    if (which == PC1) {
        while((i = consume1()) != -1) {
            //insert each value - Takes the place of BSTv1Insert
            hash_table_insert(temp, i);
        }
    }
    else if (which == PC2) {
        while((i = consume2()) != -1){
            hash_table_insert(temp, i);
        }
    }

    HSTv1GetNums(temp, hashValues);

    //get the values
    // Takes the place of BSTv1GetNums & inorder
    hash_table_print(temp);


    TIMERSTOP(HTv1)
    double treeTime = DURATION(HTv1)

    //check for correctness
    compare(sortedInput, hashValues, size);
    return treeTime;
}

void HSTv1GetNums(HashTable * ht, int * array)
{
    inorder_ht(ht, array);
}

int cmpfc(const void* a, const void* b) {
    return (*(int*)a-*(int*)b);
}

void (*cmpfc_ptr) = &cmpfc;

void inorder_ht(HashTable * ht, int * array)
{
    //TODO
    if(ht == NULL)
    {
        return;
    }
    int i = 0;
    int j = 0;
    LinkedList * cur_list = ht->table[j];
    Node * cur_node = cur_list->head;
    int size = HASH_TABLE_SIZE;
    while (cur_list != NULL) {
        while (cur_node != NULL) {
            array[i] = cur_node->data;
            cur_node = cur_node->next;
            i++;
        }
        j++;
        cur_list = ht->table[j];
        i=0;
    }

    //qsort(array, size, sizeof(int), cmpfc_ptr);
}