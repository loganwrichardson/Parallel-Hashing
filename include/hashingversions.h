// Created by Logan Richardson and Vidhi Patel on 7/27/23.

// Producer-Consumer Version 1 (uses semaphores)
#define PC1 1
// Producer-Consumer Version 2 (uses condition variables)
#define PC2 2

/**
 * last parameter to each of these indicates which version
 * of the Producer-Consumer to use
 * if which is PC1 then consume1 is called.
 * if which is PC2 then consume2 is called.
 */
double doHTv1(int * sortedInput, int numBuckets, int numNodes, int which);

double doHTv2(int * sortedInput, int numBuckets, int numNodes, int numThreads, int which);

double doHTv3(int * sortedInput, int numBuckets, int numNodes, int numThreads, int which);

double doHTv4(int * sortedInput, int numBuckets, int numNodes,  int numThreads, int which);
