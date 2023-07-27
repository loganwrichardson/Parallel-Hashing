//
// Created by Logan Richardson on 7/27/23.
//
#include <stdlib.h>
#include <semaphore.h>
#include "helpers.h"
#include "macros.h"
#include "wrappers.h"
#include "producerConsumer1.h"
#include "producerConsumer2.h"
#include "BSTversions.h"
#include "hash_table.h"


//Build the BST using just one thread (the calling thread).
//Check for correctness.
//Return the time it takes to do it.
//double doBSTv1(int * input, int * sortedInput, int size)
double doHTv1(int * sortedInput, int size, int which)
{
    int i;
    int treeValues[size];
    // Takes the place of resetBSTv1
    HashTable * temp = hash_table_create(size);


    TIMERSTART(HTv1)

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

    //get the values
    // Takes the place of BSTv1GetNums & inorder
    hash_table_print(temp);


    TIMERSTOP(HTv1)
    double treeTime = DURATION(HTv1)

    //check for correctness
    compare(sortedInput, treeValues, size);
    return treeTime;
}
