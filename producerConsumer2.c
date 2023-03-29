#include <pthread.h>
#include <stdio.h>
#include "producerConsumer2.h"
#include "wrappers.h"


/* This code implements producer-consumer using semaphores */

#define SIZE 100
//producer fills buffer; consumer empties buffer
static int buffer[SIZE];
//total used by consumer to determine how many remaining
//values will be available at some point for consumption
static int total;
//You'll need more static variables
static pthread_t * threads;
static int producer_thread;

// Condition variables
static pthread_cond_t full = PTHREAD_COND_INITIALIZER;
static pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


//Struct for the producer arg
typedef struct {
    int* input;
    int start;
    int end;
    int* buffer;
} producer_args_t;


//functions that are local to this file
static int get();
static void put();
static void * producer(void * arg);

/*
 * get
 * called by consumer to get a value from the buffer
 */
static int use = 0;
int get()
{
   int val;
   val = buffer[use];
   use = (use + 1) % SIZE;
   return val;
}

/*
 * put
 * called by producer to put a value in the buffer
 */
static int fill = 0;
void put(int ele)
{
   //decrement empty semaphore to wait for available empty slot in buffer
   buffer[fill] = ele;
   fill = (fill + 1) % SIZE;
   return;
}

/*
 * createProducers1
 * Takes as input an array of ints that will be used by the
 * producer threads to fill the buffer
 */
void createProducers2(int * input, int size, int numThreads)
{
   //Initialize total to size, which is the number of
   //remaining values that a consumer will ultimately consume
    total = size;

   //Create numThreads threads to act as producers
   //Each thread will put approximately size/numThreads
   //elements in the input array into the buffer
   //Divide up the work so that each thread handles
   //either size/numThreads or size/numThreads + 1 elements.
   producer_thread = numThreads;
   threads = (pthread_t *)Malloc(sizeof(pthread_t) * numThreads);
   int chunkSize = size / numThreads;
   int startIndex = 0;
   int endIndex = 0;
   int i;

   for (i = 0; i < numThreads; i++) {
      if (i < (size % numThreads)) {
         chunkSize = chunkSize + 1;
      } else {
         chunkSize = size / numThreads;
      }

      endIndex = startIndex + chunkSize;

      producer_args_t* pargs = malloc(sizeof(producer_args_t));
      pargs->input = input;
      pargs->start = startIndex;
      pargs->end = endIndex;
      pargs->buffer = buffer;

      Pthread_create(&threads[i], NULL, producer, pargs);

      startIndex = endIndex;
   }
}


/*
 * joinProducer1
 * Joins each of the producer threads created by the createProducers2
 * function.
 * Destroys each of the condition variables and mutex.
 */
void joinProducers2()
{
   //TODO
   int i;
   for (i = 0; i < producer_thread; i++) {
      Pthread_join(threads[i], NULL);
   }
   Pthread_mutex_destroy(&mutex);
   Pthread_cond_destroy(&full);
   Pthread_cond_destroy(&empty);
   
}

/*
 * producer
 * This is the function executed by the thread.
 * Each thread copies elements from the input array
 * into the producer-consumer buffer by calling the
 * put function. Semaphores are used to synchronize the
 * threads.
 * args is a pointer to a structure that contains
 * the arguments needed by the thread
 */
void * producer(void * args)
{
   int i;
   producer_args_t* pargs = (producer_args_t*) args;
   for (i = pargs->start; i < pargs->end; i++) {
      Pthread_mutex_lock(&mutex);
         while (fill == SIZE) {
            Pthread_cond_wait(&empty, &mutex);
         }
      put(pargs->input[i]);
      if (fill == 1) {
            Pthread_cond_signal(&full);
        }
        Pthread_mutex_unlock(&mutex);
   }
   return NULL;
}
/*void * producer(void * args)
{
   int i;
   producer_args_t* pargs = (producer_args_t*) args;

   for (i = pargs->start; i < pargs->end; i++) {
      int item = pargs->input[i];
      
      Pthread_mutex_lock(&mutex);
      
      do {
         if (fill < SIZE) {
            put(item);
            fill++;
            if (fill == 1) {
               Pthread_cond_signal(&full);
            }
            break;
         }
         Pthread_cond_wait(&empty, &mutex);
      } while (1);

      Pthread_mutex_unlock(&mutex);
   }
   
   return NULL;
}*/

/*
 * consume1
 * This function is called by the consumer (BST implementation).
 * If total is 0 then no values remain to be produced
 * for consumption so return -1.  Otherwise, consume1 calls get
 * to obtain a value from the buffer and total is decremented by 1.
 * Semaphores * are used to synchronize the threads.
 */
int consume2()
{
   Pthread_mutex_lock(&mutex);
   
   while (fill == 0 && total > 0) {
      Pthread_cond_wait(&full, &mutex);
    }

   if (total == 0 && fill == 0) {
      Pthread_mutex_unlock(&mutex);
      return -1;
   }

   int val = get();
   fill--;

   if (total > 0 && fill == SIZE - 1) {
      Pthread_cond_signal(&empty);
   }

   total--;

   Pthread_mutex_unlock(&mutex);
   
   return val;
}
