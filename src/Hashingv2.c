// Created by Logan Richardson and Vidhi Patel on 7/27/23.

#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include "helpers.h"
#include "macros.h"
#include "wrappers.h"
#include "producerConsumer1.h"
#include "producerConsumer2.h"
#include "BSTversions.h"
#include "hash_table.h"

pthread_mutex_t hash_lock = PTHREAD_MUTEX_INITIALIZER;

/**
 * Insert a value into the Hash table with only one lock
 * @param arg: void *
 * @return
 */
void * doInsert2(void *arg)
{
    int i;
    Args * myArgs = (Args*)arg;

    int which = myArgs->whichPtr;
    HashTable * ht = myArgs->ht;

    if (which == PC1) {
        while((i = consume1()) != -1) {
            // Insert each value
            pthread_mutex_lock(&hash_lock);
            hash_table_insert(ht, i);
            pthread_mutex_unlock(&hash_lock);
        }
    }
    else if (which == PC2) {
        while((i = consume2())!= -1){
            // Insert each value
            pthread_mutex_lock(&hash_lock);
            hash_table_insert(ht, i);
            pthread_mutex_unlock(&hash_lock);
        }
    }
    return NULL;
}

/**
 * Build the Hash Table using just on thread (the calling thread).
 * Check for correctness.
 * Return the time it takes to do it.
 *
 * @param sortedInput: int * sorted input to check for correctness
 * @param numBuckets: int number of buckets into which the nodes will be sorted
 * @param numNodes: int number of nodes to insert into the hash table
 * @param numThreads: int number of threads which will do the insertion
 * @param which: int which producer-consumer to use
 * @return double
 */
double doHTv2(int * sortedInput, int numBuckets, int numNodes, int numThreads, int which)
{
    int i;
    int hashValues2[numNodes];

    // Initialize Hash Table Lock
    pthread_mutex_init(&hash_lock, NULL);

    HashTable * temp = hash_table_create(numBuckets);

    TIMERSTART(HTv2)


    pthread_t threads[numThreads];
    for(i = 0; i< numThreads; i++){
        Args * myArgs = args_create(temp, which);
        Pthread_create(&threads[i], NULL, doInsert2, (void*)myArgs);
    }

    // Join the threads together
    for (i = 0; i < numThreads; i++) {
        Pthread_join(threads[i], NULL);
    }

    // Get the values
    HSTGetNums(temp, hashValues2);


    TIMERSTOP(HTv2)
    double hashTime = DURATION(HTv2)

    // Print for testing
    //hash_table_print(temp);

    // Print to check capacity
    //printf("PRINTING HASH TABLE CAPACITY %d\n", temp->capacity);

    // Print to test sorted Input & hashValues2
    //printf("\nPrinting the sortedInput from HashingV1.c\n");
    //printNums(sortedInput, numNodes);
    //printf("\nPrinting the hashValues from HashingV2.c\n");
    //printNums(hashValues2, numNodes);
    //printf("\n")

    // Check for correctness
    int testSize = numNodes - 1;
    compare(sortedInput, hashValues2, testSize);
    return hashTime;
}
