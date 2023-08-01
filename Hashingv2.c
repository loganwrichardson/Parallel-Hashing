//
// Created by Logan Richardson on 7/27/23.
//

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
static HashTable *ht = NULL;

// Insert a value into the Hash Table with a lock
void * doInsert(void *arg)
{
    int i;
    //int which = *(int*)arg;
    Args * myArgs = (Args*)arg;

    int which = myArgs->whichPtr;
    HashTable * ht = myArgs->ht;

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
    int hashValues2[size];

    // Initialize global lock
    pthread_mutex_init(&hash_lock, NULL);

    // Takes the place of resetBSTv1
    HashTable * temp = hash_table_create(size);

    TIMERSTART(HTv2)

    pthread_t threads[numThreads];
    for(i = 0; i< numThreads; i++){

        Args * myArgs = args_create(temp, which);

        // Old Code
        //int* whichPtr = (int*)Malloc(sizeof(int));
        //*whichPtr = which;
        //Pthread_create(&threads[i], NULL, doInsert, whichPtr);

        Pthread_create(&threads[i], NULL, doInsert, (void*)myArgs);
    }

    // unlock tree after all threads are done
    for (i = 0; i < numThreads; i++) {
        Pthread_join(threads[i], NULL);
    }

    //get the values
    HSTv2GetNums(temp, hashValues2);


    //Print for testing
    hash_table_print(temp);


    TIMERSTOP(HTv2)
    double hashTime = DURATION(HTv2)

    printf("\nPrinting the sortedInput from HashingV1.c");
    printNums(sortedInput, size);
    printf("\nPrinting the hashValues from HashingV2.c");
    printNums(hashValues2, size);
    printf("\n");

    //check for correctness
    compare(sortedInput, hashValues2, size);
    return hashTime;
}

void HSTv2GetNums(HashTable * ht, int * array)
{
    inorder_ht(ht, array);
}

Args* args_create(HashTable * ht, int whichPtr) {
    Args * args = calloc(1, sizeof(Args*));
    args->whichPtr = *(int*)Malloc(sizeof(int));
    args->whichPtr = whichPtr;
    args->ht = ht;
    return args;
}
