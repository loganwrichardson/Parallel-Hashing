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

/**
 * Insert a value into the Hash Table with X threads and a lock for each node.
 * @param arg: void *
 * @return
 */
void * doInsert3(void *arg)
{
    int i;
    Args * myArgs = (Args*)arg;

    int which = myArgs->whichPtr;
    HashTable * ht = myArgs->ht;

    if (which == PC1) {
        while((i = consume1()) != -1) {
            hash_table_insert_with_node_locks(ht, i);
        }
    }
    else if (which == PC2) {
        while((i = consume2())!= -1){
            hash_table_insert_with_node_locks(ht, i);
        }
    }
    return NULL;
}

/**
 * Build the Hash table using X threads and a lock for each node
 * @param sortedInput: int * sorted input to check for correctness
 * @param numBuckets: int number of buckets into which the nodes will be sorted
 * @param numNodes: int number of nodes to insert into the hash table
 * @param numThreads: int number of threads which will do the insertion
 * @param which: int which producer-consumer to use
 * @return double
 */
double doHTv3(int * sortedInput, int numBuckets, int numNodes, int numThreads, int which)
{
    int i;
    int hashValues3[numNodes];

    HashTable * temp = hash_table_create(numBuckets);

    TIMERSTART(HTv3)


    pthread_t threads[numThreads];
    for(i = 0; i< numThreads; i++){
        Args * myArgs = args_create(temp, which);
        Pthread_create(&threads[i], NULL, doInsert3, (void*)myArgs);
    }

    // Join the threads together
    for (i = 0; i < numThreads; i++) {
        Pthread_join(threads[i], NULL);
    }

    // Get the values
    HSTGetNums(temp, hashValues3);


    TIMERSTOP(HTv3)
    double hashTime = DURATION(HTv3)

    // Print for testing
    //hash_table_print(temp);

    // Print to check capacity
    //printf("PRINTING HASH TABLE CAPACITY %d\n", temp->capacity);

    // Print to test sorted Input & hashValues3
    //printf("\nPrinting the sortedInput from HashingV1.c\n");
    //printNums(sortedInput, numNodes);
    //printf(\nPrinting the hashValues from HashingV3.c\n");
    //printNums(hashValues3, numNodes);
    //printf("\n");

    // Check for correctness
    int testSize = numNodes - 1;
    compare(sortedInput, hashValues3, testSize);
    return hashTime;
}