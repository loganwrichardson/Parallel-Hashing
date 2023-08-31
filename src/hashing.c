// Created by Logan Richardson & Vidhi Patel on 8/4/23.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "producerConsumer1.h"
#include "producerConsumer2.h"
#include "hash_table.h"
#include "hashingversions.h"
#include "helpers.h"

int main(int argc, char * argv[])
{
    int numBuckets, numNodes, numConsume, numProduce;
    getArgsHash(argc, argv, &numBuckets, &numNodes, &numConsume, &numProduce);

    int * input = malloc(sizeof(int) * numNodes);
    int * sortedInput = malloc(sizeof(int) * numNodes);

    //randomly generate some input
    makeInput(input, numNodes);
    memcpy(sortedInput, input, sizeof(int) * numNodes);
    printf("Sorting the input to check for correctness (n = %d).\n",
           numNodes);

    // Print to test input
    //printNums(input, numNodes);
    //printf("\n");

    // Print to test sortedInput
    //printNums(sortedInput, numNodes);
    //printf("\n");

    // Print to test numBuckets & numNodes
    //printf("numBuckets = %d\n", numBuckets);
    //printf("numNodes = %d\n", numNodes);

    runHashingWithProducerConsumer1(input, sortedInput, numBuckets, numNodes,
                                    numConsume, numProduce, PC1);
    runHashingWithProducerConsumer2(input, sortedInput, numBuckets, numNodes,
                                    numConsume, numProduce, PC2);

    return 0;
}

/**
 * Build the hash table using a producer-consumer that is implemented using semaphores
 * @param input: int * values to insert into the hash table (provided to the producer)
 * @param sortedInput: int * sorted input to check for correctness
 * @param numBuckets: int number of buckets into which the nodes will be sorted
 * @param numNodes: int number of nodes to insert into the hash table
 * @param numConsume: int number of threads created to inserted into hash table
 * @param numProduce: int number of threads that will be used to fill the producer - consumer buffer
 * @param which: int which producer-consumer to use
 */
void runHashingWithProducerConsumer1(int * input, int * sortedInput, int numBuckets, int numNodes,
                                      int numConsume, int numProduce, int which)
{
    double hashTime;

    printf("\nUsing %d threads to produce data for each Hash Table.\n",
           numProduce);
    printf("Producer/consumer implemented using semaphores.\n");

    printf("\nBuilding hash table with 1 thread.\n");
    createProducers1(input, numNodes, numProduce);
    hashTime = doHTv1(sortedInput, numBuckets, numNodes, which);
    joinProducers1();
    printf("Time: %f sec\n", hashTime);

    printf("\nBuilding hash table with %d threads and one lock per Hash Table.\n", numConsume);
    createProducers1(input, numNodes, numProduce);
    hashTime = doHTv2(sortedInput, numBuckets, numNodes, numConsume, which);
    joinProducers1();
    printf("Time: %f sec\n", hashTime);

    printf("\nBuilding hash table with %d threads and one lock per node.\n", numConsume);
    createProducers1(input, numNodes, numProduce);
    hashTime = doHTv3(sortedInput, numBuckets, numNodes, numConsume, which);
    joinProducers1();
    printf("Time: %f sec\n", hashTime);

    printf("\nBuilding hash table with %d threads and no locks.\n", numConsume);
    createProducers1(input, numNodes, numProduce);
    hashTime = doHTv4(sortedInput, numBuckets, numNodes, numConsume, which);
    joinProducers1();
    printf("Time: %f sec\n", hashTime);
}

/**
 * Build the hash table using a producer-consumer that is implemented using condition variables
 * @param input: int * values to insert into the hash table (provided to the producer)
 * @param sortedInput: int * sorted input to check for correctness
 * @param numBuckets: int number of buckets into which the nodes will be sorted
 * @param numNodes: int number of nodes to insert into the hash table
 * @param numConsume: int number of threads created to inserted into hash table
 * @param numProduce: int number of threads that will be used to fill the producer - consumer buffer
 * @param which: int which producer-consumer to use
 */
void runHashingWithProducerConsumer2(int * input, int * sortedInput, int numBuckets, int numNodes,
                                     int numConsume, int numProduce, int which)
{
    double hashTime;

    printf("\nUsing %d threads to produce data for each Hash Table.\n",
           numProduce);
    printf("Producer/consumer implemented using condition variables.\n");

    printf("\nBuilding hash table with 1 thread.\n");
    createProducers2(input, numNodes, numProduce);
    hashTime = doHTv1(sortedInput, numBuckets, numNodes, which);
    joinProducers2();
    printf("Time: %f sec\n", hashTime);

    printf("\nBuilding hash table with %d threads and one lock per tree.\n",
           numConsume);
    createProducers2(input, numNodes, numProduce);
    hashTime = doHTv2(sortedInput, numBuckets, numNodes, numConsume, which);
    joinProducers2();
    printf("Time: %f sec\n", hashTime);

    printf("\nBuilding hash table with %d threads and one lock per node.\n",
           numConsume);
    createProducers2(input, numNodes, numProduce);
    hashTime = doHTv3(sortedInput, numBuckets, numNodes, numConsume, which);
    joinProducers2();
    printf("Time: %f sec\n", hashTime);

    printf("\nBuilding hash table with %d threads and no locks.\n", numConsume);
    createProducers2(input, numNodes, numProduce);
    hashTime = doHTv4(sortedInput, numBuckets, numNodes, numConsume, which);
    joinProducers2();
    printf("Time: %f sec\n", hashTime);
}

