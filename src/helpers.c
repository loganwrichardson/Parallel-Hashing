#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "helpers.h"

/**
 * Compare the values in the correctValues to the
 * values in arrayValues to see if they match
 * @param correctValues: int * correctly sorted/inserted values to compare against
 * @param arrayValues: int * values from the sorting algorithm you are checking
 * @param size: int num values to compare
 */
void compare(int * correctValues, int * arrayValues, int size)
{
   int i;
   for (i = 0; i < size; i++)
   {
      if (correctValues[i] != arrayValues[i])
      {
         printf("Error at index %d: correct value is %d, your value is %d\n",
                i, correctValues[i], arrayValues[i]);
         exit(1);
      }
   }
}

/**
 * Prints out the elements of the array
 * Useful for debugging
 * @param nums: int *
 * @param size: int
 */
void printNums(int * nums, int size)
{
   int i;
   for (i = 0; i < size; i++)
   {
      if ((i % 10) == 0) printf("\n");
      printf("%d ", nums[i]);
   }
}

///**
// * getArgsBST
// * Parse the command line argument to get the number of values to insert into the BST,
// * the number of consumer threads, and the number of producer threads
// * @param argc: int the number of command line arguments
// * @param argv: char * the array of command line arguments
// * @param size: int * pointer to int to be set to the number of values to be inserted into the BST
// * @param numConsume int * pointer to int to be set to the number of consumer threads to get a value from
// * the producer-consumer buffer and insert into the BST
// * @param numProduce int * pointer to the int to be set to the number of producer threads
// * to fill the producer-consumer buffer
// */
//void getArgsBST(int argc, char * argv[], int * size,
//             int * numConsume, int * numProduce)
//{
//    char opt;
//    (*size) = BST_DEFAULT_SIZE;
//    (*numConsume) = NUMCONSUME_DEFAULT;
//    (*numProduce) = NUMPRODUCE_DEFAULT;
//    while((opt = getopt(argc, argv, "s:c:p:h")) != -1)
//    {
//        switch (opt)
//        {
//            case 'c':
//                //number of consumers
//                (*numConsume) = atoi(optarg);
//                if ((*numConsume) <= 1)
//                {
//                    fprintf(stderr, "bad -c option: Number of ");
//                    fprintf(stderr, "consumer threads needs to be > 1\n");
//                    printUsage();
//                }
//                break;
//            case 'p':
//                //number of producers
//                (*numProduce) = atoi(optarg);
//                if ((*numProduce) <= 1)
//                {
//                    fprintf(stderr, "bad -p option: Number of ");
//                    fprintf(stderr, "producer threads needs to be > 1\n");
//                    printUsage();
//                }
//                break;
//            case 's':
//                (*size) = atoi(optarg);
//                if ((*size) <= 0)
//                {
//                    fprintf(stderr, "bad -s option: Number of ");
//                    fprintf(stderr, "values to insert needs to be > 0\n");
//                    printUsage();
//                }
//                break;
//            case 'h':
//                printUsage();
//            case '?':
//                printUsage();
//
//        }
//    }
//}

/**
 * getArgsHash
 * Parse the command line argument to get the number of values to insert into the BST,
 * the number of consumer threads, and the number of producer threads
 * @param argc: int the number of command line arguments
 * @param argv: char * the array of command line arguments
 * @param numBuckets: int * pointer to int to be set to the number of buckets
 * @param numNodes: int * pointer to int to be set to the number of Nodes to insert into the Hash Table
 * @param numConsume int * pointer to int to be set to the number of consumer threads to get a value from
 * the producer-consumer buffer and insert into the BST
 * @param numProduce int * pointer to the int to be set to the number of producer threads
 * to fill the producer-consumer buffer
 */
void getArgsHash(int argc, char * argv[], int * numBuckets, int * numNodes,
             int * numConsume, int * numProduce)
{
    char opt;
    (*numBuckets) = NUMBUCKETS_DEFAULT;
    (*numNodes) =  NUMNODES_DEFAULT;
    (*numConsume) = NUMCONSUME_DEFAULT;
    (*numProduce) = NUMPRODUCE_DEFAULT;
    while((opt = getopt(argc, argv, "b:n:c:p:h")) != -1)
    {
        switch (opt)
        {
            case 'c':
                //number of consumers
                (*numConsume) = atoi(optarg);
                if ((*numConsume) <= 1)
                {
                    fprintf(stderr, "bad -c option: Number of ");
                    fprintf(stderr, "consumer threads needs to be > 1\n");
                    printUsage();
                }
                break;
            case 'p':
                //number of producers
                (*numProduce) = atoi(optarg);
                if ((*numProduce) <= 1)
                {
                    fprintf(stderr, "bad -p option: Number of ");
                    fprintf(stderr, "producer threads needs to be > 1\n");
                    printUsage();
                }
                break;
            case 'b':
                (*numBuckets) = atoi(optarg);
                if ((*numBuckets) <= 0)
                {
                    fprintf(stderr, "bad -b option: Number of ");
                    fprintf(stderr, "values to insert needs to be > 0\n");
                    printUsage();
                }
                break;
            case 'n':
                (*numNodes) = atoi(optarg);
                if ((*numNodes) <= 0)
                {
                    fprintf(stderr, "bad -n option: Number of ");
                    fprintf(stderr, "values to insert needs to be > 0\n");
                    printUsage();
                }
                break;
            case 'h':
                printUsage();
            case '?':
                printUsage();

        }
    }
}

/**
 * Print usage
 * Print the usage information and exit.
 */
void printUsage()
{
    printf("usage: ./hash [-s <numNodes>] [-c <cthreads>] [-p <pthreads> ] [ -h ] \n");
    printf("       <numNodes> is the number of nodes to insert\n");
    printf("              default: %d\n", NUMNODES_DEFAULT);
    printf("       <numBuckets> is the number of buckets to sort into\n");
    printf("              default: %d\n", NUMBUCKETS_DEFAULT);
    printf("       <cthreads> is the number of consumer threads to use\n");
    printf("              default: %d\n", NUMCONSUME_DEFAULT);
    printf("       <threads> is the number of producer threads to use\n");
    printf("              default: %d\n", NUMPRODUCE_DEFAULT);
    printf("       -h print usage info and exit\n");
    exit(1);
}

/**
 * makeInput
 * Randomly generates size numbers within the range
 * 0 and (size * 2)-1 [inclusive]. Fills the nums array
 * with those values.
 * @param nums: int * array to store the numbers
 * @param size: int amount of numbers to generate
 */
void makeInput(int * nums, int size)
{
    int used[size << 1];
    int i, j;
    int newNum;

    for (i = 0; i < (size << 1); i++) used[i] = 0;

    j = 0;
    while (j < size)
    {
        newNum = random() % (size << 1);
        if (used[newNum] == 0)
        {
            nums[j] = newNum;
            used[newNum] = 1;
            j++;
        }
    }
}

/**
 * sortInput
 * sort the nums array using an insertion sort
 * @param nums: int * array to to be sorted
 * @param size: int size of the array
 */
void sortInput(int * nums, int size)
{
    int i, j, insert;
    for (i = 1; i < size; i++)
    {
        insert = nums[i];
        for (j = i-1; j >= 0; j--)
        {
            if (nums[j] > insert)
            {
                nums[j+1] = nums[j];
                nums[j] = insert;
            }
        }
    }
}