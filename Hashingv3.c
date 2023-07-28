////
//// Created by Logan Richardson on 7/27/23.
////
//#include <stdlib.h>
//#include <semaphore.h>
//#include <pthread.h>
//#include "helpers.h"
//#include "macros.h"
//#include "wrappers.h"
//#include "producerConsumer1.h"
//#include "producerConsumer2.h"
//#include "BSTversions.h"
//#include "Hashingv3.h"
//
//pthread_mutex_t hash_lock = PTHREAD_MUTEX_INITIALIZER;
//static HTv3 *ht = NULL;
//
//// Insert a value into the BST with a lock
//void * doInsert(void *arg)
//{
//    int i;
//    int which = *(int*)arg;
//    if (which == PC1) {
//        while((i = consume1()) != -1) {
//            //insert each value
//            Pthread_mutex_lock(&hash_lock);
//            hash_table_insert3(ht, i);
//            Pthread_mutex_unlock(&hash_lock);
//        }
//    }
//    else if (which == PC2) {
//        while((i = consume2())!= -1){
//            Pthread_mutex_lock(&hash_lock);
//            hash_table_insert3(ht, i);
//            Pthread_mutex_unlock(&hash_lock);
//        }
//    }
//    return NULL;
//}
//
//
////Build the BST using just one thread (the calling thread).
////Check for correctness.
////Return the time it takes to do it.
////double doBSTv1(int * input, int * sortedInput, int size)
//double doHTv2(int * sortedInput, int size, int numThreads, int which)
//{
//    int i;
//    int treeValues[size];
//
//    // Initialize global lock
//    pthread_mutex_init(&hash_lock, NULL);
//
//    // Takes the place of resetBSTv1
//    ht = hash_table_create3(size);
//
//    TIMERSTART(HTv2)
//
//    pthread_t threads[numThreads];
//    for(i = 0; i< numThreads; i++){
//        int* whichPtr = (int*)Malloc(sizeof(int));
//        *whichPtr = which;
//        Pthread_create(&threads[i], NULL, doInsert, whichPtr);
//    }
//
//    // unlock tree after all threads are done
//    for (i = 0; i < numThreads; i++) {
//        Pthread_join(threads[i], NULL);
//    }
//
//
//    //get the values
//    // Takes the place of BSTv1GetNums & inorder
//    hash_table_print3(ht);
//
//
//    TIMERSTOP(HTv2)
//    double treeTime = DURATION(HTv2)
//
//    //check for correctness
//    compare(sortedInput, treeValues, size);
//    return treeTime;
//}
//
//HTv3 * hash_table_create3(int capacity) {
//    int i;
//
//    // Creates the hash table in memory
//    HTv3 *ht = calloc(1, sizeof *ht);
//    // Sets the hash table capacity
//    ht->capacity = capacity;
//    // allocates memory for the number of linked lists
//    ht->table = calloc(ht->capacity, sizeof *(ht->table));
//    // allocate memory for each linked list in the array
//
//    for(i=0; i < ht->capacity; i++){
//        ht->table[i] = linked_list_create();
//    }
//
//    // return the pointer to the array of empty linked lists
//    return ht;
//}
//
///**
// * Universal Hash Function
// * h(k) = ((ak + b) mod p) mod m (p is prime or relatively prime with m;
// * @param key: int
// * @return int
// */
//int hash_func3(HTv3 *ht, int key) {
//    return (int)((2971 * key + 101923) % 128189) % ht->capacity;
//}
//
//void hash_table_insert3(HTv3 * ht, int data) {
//    // Get the hash key
//    int key = hash_func3(ht, data);
//    // Insert the data
//    linked_list_insert(ht->table[key], data);
//    return;
//}
//
//void hash_table_remove3(HTv3 *ht, int data) {
//    int key = hash_func3(ht, data);
//    linked_list_remove(ht->table[key], data);
//}
//
//void hash_table_print3(HTv3 *ht) {
//    int i;
//
//    for(i = 0; i < ht->capacity; i++) {
//        linked_list_print(ht->table[i]);
//    }
//    return;
//}
