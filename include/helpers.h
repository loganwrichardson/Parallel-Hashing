// Created by Logan Richardson & Vidhi Patel on 8/4/23

// Helper functions used by the hashing versions and bst versions

void printNums(int * nums, int size);

void compare(int * correctValues, int * bstValues, int size);

void makeInput(int * nums, int size);

void sortInput(int * nums, int size);

void getArgsBST(int argc, char * argv[], int * size, int * numConsume, int * numProduce);

void getArgsHash(int argc, char * argv[], int * numBuckets, int * numNodes, int * numConsume, int * numProduce);

void printUsage();

#define NUMBUCKETS_DEFAULT 100 // Controls the number of buckets
#define NUMNODES_DEFAULT 100000 // Controls the number of nodes
#define NUMCONSUME_DEFAULT 4 // Controls the number of consumers
#define NUMPRODUCE_DEFAULT 4 // Controls the number of producers
