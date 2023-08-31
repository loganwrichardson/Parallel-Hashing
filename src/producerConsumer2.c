#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include "producerConsumer2.h"
#include "wrappers.h"
#include <stdlib.h>
#include <pthread.h>


/* This code implements producer-consumer using semaphores */
typedef struct {
    int * input;
    int startIdx;
    int endIdx;
} prodArg_t;

#define SIZE 100
//producer fills buffer; consumer empties buffer
static int buffer[SIZE];

//total used by consumer to determine how many remaining
//values will be available at some point for consumption
static int total;

//You'll need more static variables
static int nThreads;
pthread_t* threads;
prodArg_t* arguments;
static int fill = 0;
static int use = 0;
static int count = 0;

pthread_cond_t empty, full;
pthread_mutex_t mutex, totalMutex;

//functions that are local to this file
static int get();
static void put();
static void * producer(void * arg);

/**
 * get
 * called by consumer to get a value from the buffer
 */
int get()
{

    int val = buffer[use];
    use = (use + 1) % SIZE;
    count--;
    return val;
}

/**
 * put
 * called by producer to put a value in the buffer
 */
void put(int ele)
{
    buffer[fill] = ele;
    fill = (fill + 1) % SIZE;
    count++;
}

void createProducers2(int * input, int size, int numThreads)
{
    threads = (pthread_t*)Malloc(numThreads * sizeof(pthread_t));
    arguments = (prodArg_t*)Malloc(numThreads * sizeof(prodArg_t));

    Pthread_mutex_init(&mutex, NULL);
    Pthread_mutex_init(&totalMutex, NULL);
    Pthread_cond_init(&empty, NULL);
    Pthread_cond_init(&full, NULL);

    total = size;

    int amountPerThread = size / numThreads;
    int remain = size - (amountPerThread * numThreads);
    int amountToProcess;
    int startIdx = 0;
    int endIdx;

    nThreads = numThreads;

    int i;
    for (i = 0; i < numThreads; i++) {
        amountToProcess = amountPerThread;
        if (remain > 0) {
            amountToProcess++;
            remain--;
        }
        endIdx = startIdx + amountToProcess;

        prodArg_t args = { input, startIdx, endIdx };
        arguments[i] = args;

        Pthread_create(&threads[i], NULL, producer, &arguments[i]);

        startIdx += amountToProcess;
    }

}

void joinProducers2() {
    int i;
    for (i = 0; i < nThreads; i++) {
        (void) pthread_join(threads[i], NULL);
    }
    Pthread_mutex_destroy(&totalMutex);
    Pthread_mutex_destroy(&mutex);
    Pthread_cond_destroy(&empty);
    Pthread_cond_destroy(&full);
    free(threads);
    free(arguments);
}


void * producer(void * args)
{
    prodArg_t *aments = (prodArg_t *) args;
    
    int i;
    for (i = aments->startIdx; i < aments->endIdx; i++) {
        Pthread_mutex_lock(&mutex);
        while (count == SIZE) {
            Pthread_cond_wait(&empty, &mutex);
        }
        put(aments->input[i]);
        Pthread_cond_signal(&full);
        Pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int consume2() {
    Pthread_mutex_lock(&totalMutex);
    if (total == 0) {
        Pthread_mutex_unlock(&totalMutex);
        return -1;
    }
    else {
        total--;
    }
    Pthread_mutex_unlock(&totalMutex);
    Pthread_mutex_lock(&mutex);
    while(count == 0) {
        Pthread_cond_wait(&full, &mutex);
    }
    int val = get();
    Pthread_cond_signal(&empty);
    Pthread_mutex_unlock(&mutex);
    return val;
}