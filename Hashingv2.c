//
// Created by Logan Richardson on 7/27/23.
//

#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "helpers.h"
#include "macros.h"
#include "wrappers.h"
#include "producerConsumer1.h"
#include "producerConsumer2.h"
#include "BSTversions.h"
#include "hash_table.h"

pthread_mutex_t hash_lock = PTHREAD_MUTEX_INITIALIZER;
static HashTable *ht = NULL;

// Insert a value into the BST with a lock
void * doInsert(void *arg)
{
    int i;
    int which = *(int*)arg;
    if (which == PC1) {
        while((i = consume1()) != -1) {
            //insert each value
            Pthread_mutex_lock(&hash_lock);
            hash_table_insert(ht, i);
            Pthread_mutex_unlock(&hash_lock);
        }
    }
    else if (which == PC2) {
        while((i = consume2())!= -1){
            Pthread_mutex_lock(&hash_lock);
            hash_table_insert(ht, i);
            Pthread_mutex_unlock(&hash_lock);
        }
    }
    return NULL;
}


//Build the BST using just one thread (the calling thread).
//Check for correctness.
//Return the time it takes to do it.
//double doBSTv1(int * input, int * sortedInput, int size)
double doHTv2(int * sortedInput, int size, int numThreads, int which)
{
    int i;
    int treeValues[size];

    // Initialize global lock
    pthread_mutex_init(&hash_lock, NULL);

    // Takes the place of resetBSTv1
    ht = hash_table_create(size);

    TIMERSTART(HTv2)

    pthread_t threads[numThreads];
    for(i = 0; i< numThreads; i++){
        int* whichPtr = (int*)Malloc(sizeof(int));
        *whichPtr = which;
        Pthread_create(&threads[i], NULL, doInsert, whichPtr);
    }

    // unlock tree after all threads are done
    for (i = 0; i < numThreads; i++) {
        Pthread_join(threads[i], NULL);
    }


    //get the values
    // Takes the place of BSTv1GetNums & inorder
    hash_table_print(ht);


    TIMERSTOP(HTv2)
    double treeTime = DURATION(HTv2)

    //check for correctness
    compare(sortedInput, treeValues, size);
    return treeTime;
}
