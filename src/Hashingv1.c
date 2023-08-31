// Created by Logan Richardson and Vidhi Patel on 7/27/23.

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>
#include "helpers.h"
#include "macros.h"
#include "wrappers.h"
#include "producerConsumer1.h"
#include "producerConsumer2.h"
#include "hash_table.h"
#include "hashingversions.h"

/**
 * Build the Hash Table using just one thread (the calling thread).
 * Check for correctness.
 * Return the time it takes to do it.
 *
 * @param sortedInput: int * sorted input to check for correctness
 * @param numBuckets: int number of buckets into which the nodes will be sorted
 * @param numNodes: int number of nodes to insert into the hash table
 * @param which: int which producer-consumer to use
 * @return double
 *
 */
double doHTv1(int * sortedInput, int numBuckets, int numNodes, int which)
{
    int i;
    int hashValues[numNodes];

    HashTable * temp = hash_table_create(numBuckets);

    TIMERSTART(HTv1)

    if (which == PC1) {
        while((i = consume1()) != -1) {
            // Insert each value
            hash_table_insert(temp, i);
        }
    }
    else if (which == PC2) {
        while((i = consume2()) != -1){
            hash_table_insert(temp, i);
        }
    }

    HSTGetNums(temp, hashValues);
    memcpy(sortedInput, hashValues, sizeof(int) * numNodes);

    // Print for testing
    //printNums(sortedInput, numNodes);
    //printf("\n");

    //  Print for testing
    //hash_table_print(temp);

    // Print to test sorted Input & hashValues
    //printf("\nPrinting the sortedInput from HashingV1.c\n");
    //printNums(sortedInput, numNodes);
    //printf("\nPrinting the hashValues from HashingV1.c\n");
    //printNums(hashValues, numNodes);
    //printf("\n");

    TIMERSTOP(HTv1)
    double hashTime = DURATION(HTv1)

    // Check for correctness
    compare(sortedInput, hashValues, numNodes);
    return hashTime;
}