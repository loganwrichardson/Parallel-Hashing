#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "BSTversions.h"
#include "producerConsumer1.h"
//TODO
//uncomment this when ready
#include "producerConsumer2.h"
#include "hash_table.h"
#include"hashingversions.h"

//static makes these local to this file
static void makeInput(int * nums, int size);
static void sortInput(int * nums, int size);
static void getArgs(int argc, char * argv[], int * size,
                    int * numConsume, int * numProduce);
static void printUsage();
static void runBSTWithProducerConsumer1(int * input, int * sortedInput,
                                        int size, int numConsume,
                                        int numProduce, int which);
static void runBSTWithProducerConsumer2(int * input, int * sortedInput,
                                        int size, int numConsume,
                                        int numProduce, int which);
static void runHashingWithProducerConsumer1(int * input, int * sortedInput, int size,
                               int numConsume, int numProduce, int which);

//default tree size and default number of threads
#define SIZE_DEFAULT 5000
#define NUMCONSUME_DEFAULT 4
#define NUMPRODUCE_DEFAULT 4

int main(int argc, char * argv[])
{
   int size;
   int numConsume, numProduce;
   getArgs(argc, argv, &size, &numConsume, &numProduce);

   int * input = malloc(sizeof(int) * size);
   int * sortedInput = malloc(sizeof(int) * size);

   //randomly generate some input
   makeInput(input, size);
   memcpy(sortedInput, input, sizeof(int) * size);

    printf("Sorting the input to check for correctness (n = %d).\n",
          size);
   //sort the input to check for correctness
   sortInput(sortedInput, size);

//   //ProducerConsumer1 is implemented using semaphores
//   runBSTWithProducerConsumer1(input, sortedInput, size,
//                               numConsume, numProduce, PC1);
//
//   //ProducerConsumer2 is implemented using Condition Variables
//   //TODO
//   //uncomment this when ready
//   runBSTWithProducerConsumer2(input, sortedInput, size,
//                              numConsume, numProduce, PC2);

    runHashingWithProducerConsumer1(input, sortedInput, size,
                               numConsume, numProduce, PC1);
   return 0;
}

/*
 * runBSTWithProducerConsumer1
 * Build the BST using a producer-consumer that is implemented using
 * semaphores.
 * input - values to insert into BST (provided to producer)
 * sortedInput - sorted input to check for correctness
 *  (provided to consumer, which is the BST implementation)
 * size - length of the input and sortedInput arrays
 * numConsume - number of threads created to inserted into BST
 * numProduce - number of threads that will be used to fill the
 *  producer-consumer buffer
 * which - which producer-consumer to use
*/
void runBSTWithProducerConsumer1(int * input, int * sortedInput, int size,
                                 int numConsume, int numProduce, int which)
{
   double treeTime;

   printf("\nUsing %d threads to produce data for each BST.\n",
          numProduce);
   printf("Producer/consumer implemented using semaphores.\n");

   printf("\nBuilding trees with 1 thread.\n");
   createProducers1(input, size, numProduce);
   treeTime = doBSTv1(sortedInput, size, which);
    joinProducers1();
   printf("Time: %f sec\n", treeTime);

   printf("\nBuilding trees with %d threads and one lock per tree.\n", numConsume);
   createProducers1(input, size, numProduce);
   treeTime = doBSTv2(sortedInput, size, numConsume, which);
   joinProducers1();
   printf("Time: %f sec\n", treeTime);

   printf("\nBuilding trees with %d threads and one lock per node.\n", numConsume);
   createProducers1(input, size, numProduce);
   treeTime = doBSTv3(sortedInput, size, numConsume, which);
   joinProducers1();
   printf("Time: %f sec\n", treeTime);

   printf("\nBuilding trees with %d threads and no locks.\n", numConsume);
   createProducers1(input, size, numProduce);
   treeTime = doBSTv4(sortedInput, size, numConsume, which);
   joinProducers1();
   printf("Time: %f sec\n", treeTime);
}

/*
 * runBSTWithProducerConsumer2
 * Build the BST using a producer-consumer that is implemented using
 * condition variables.
 * input - values to insert into BST (provided to producer)
 * sortedInput - sorted input to check for correctness
 *  (provided to consumer, which is the BST implementation)
 * size - length of the input and sortedInput arrays
 * numConsume - number of threads created to inserted into BST
 * numProduce - number of threads that will be used to fill the
 *  producer-consumer buffer
 * which - which producer-consumer to use
*/
void runBSTWithProducerConsumer2(int * input, int * sortedInput, int size,
                                 int numConsume, int numProduce, int which)
{
   double treeTime;

   printf("\nUsing %d threads to produce data for each BST.\n",
          numProduce);
   printf("Producer/consumer implemented using condition variables.\n");

   printf("\nBuilding trees with 1 thread.\n");
   createProducers2(input, size, numProduce);
   treeTime = doBSTv1(sortedInput, size, which);
   joinProducers2();
   printf("Time: %f sec\n", treeTime);

   printf("\nBuilding trees with %d threads and one lock per tree.\n",
          numConsume);
   createProducers2(input, size, numProduce);
   treeTime = doBSTv2(sortedInput, size, numConsume, which);
   joinProducers2();
   printf("Time: %f sec\n", treeTime);

   printf("\nBuilding trees with %d threads and one lock per node.\n",
          numConsume);
   createProducers2(input, size, numProduce);
   treeTime = doBSTv3(sortedInput, size, numConsume, which);
   joinProducers2();
   printf("Time: %f sec\n", treeTime);

    printf("\nBuilding trees with %d threads and no locks.\n", numConsume);
   createProducers2(input, size, numProduce);
   treeTime = doBSTv4(sortedInput, size, numConsume, which);
   joinProducers2();
   printf("Time: %f sec\n", treeTime);

}

/*
 * runBSTWithProducerConsumer1
 * Build the BST using a producer-consumer that is implemented using
 * semaphores.
 * input - values to insert into BST (provided to producer)
 * sortedInput - sorted input to check for correctness
 *  (provided to consumer, which is the BST implementation)
 * size - length of the input and sortedInput arrays
 * numConsume - number of threads created to inserted into BST
 * numProduce - number of threads that will be used to fill the
 *  producer-consumer buffer
 * which - which producer-consumer to use
*/
void  runHashingWithProducerConsumer1(int * input, int * sortedInput, int size,
                                 int numConsume, int numProduce, int which)
{
    double treeTime;

    printf("\nUsing %d threads to produce data for each Hash Table.\n",
           numProduce);
    printf("Producer/consumer implemented using semaphores.\n");

    printf("\nBuilding trees with 1 thread.\n");
    createProducers1(input, size, numProduce);
    treeTime = doHTv1(sortedInput, size, which);
    joinProducers1();
    printf("Time: %f sec\n", treeTime);

//    printf("\nBuilding trees with %d threads and one lock per Hash Table.\n", numConsume);
//    createProducers1(input, size, numProduce);
//    treeTime = doHTv2(sortedInput, size, numConsume, which);
//    joinProducers1();
//    printf("Time: %f sec\n", treeTime);
//
//    printf("\nBuilding trees with %d threads and one lock per node.\n", numConsume);
//    createProducers1(input, size, numProduce);
//    treeTime = doBSTv3(sortedInput, size, numConsume, which);
//    joinProducers1();
//    printf("Time: %f sec\n", treeTime);

//    printf("\nBuilding trees with %d threads and no locks.\n", numConsume);
//    createProducers1(input, size, numProduce);
//    treeTime = doBSTv4(sortedInput, size, numConsume, which);
//    joinProducers1();
//    printf("Time: %f sec\n", treeTime);
}

/*
 * runBSTWithProducerConsumer2
 * Build the BST using a producer-consumer that is implemented using
 * condition variables.
 * input - values to insert into BST (provided to producer)
 * sortedInput - sorted input to check for correctness
 *  (provided to consumer, which is the BST implementation)
 * size - length of the input and sortedInput arrays
 * numConsume - number of threads created to inserted into BST
 * numProduce - number of threads that will be used to fill the
 *  producer-consumer buffer
 * which - which producer-consumer to use
*/
void runHashingWithProducerConsumer2(int * input, int * sortedInput, int size,
                                 int numConsume, int numProduce, int which)
{
    double treeTime;

    printf("\nUsing %d threads to produce data for each BST.\n",
           numProduce);
    printf("Producer/consumer implemented using condition variables.\n");

    printf("\nBuilding trees with 1 thread.\n");
    createProducers2(input, size, numProduce);
    treeTime = doBSTv1(sortedInput, size, which);
    joinProducers2();
    printf("Time: %f sec\n", treeTime);

//    printf("\nBuilding trees with %d threads and one lock per tree.\n",
//           numConsume);
//    createProducers2(input, size, numProduce);
//    treeTime = doBSTv2(sortedInput, size, numConsume, which);
//    joinProducers2();
//    printf("Time: %f sec\n", treeTime);
//
//    printf("\nBuilding trees with %d threads and one lock per node.\n",
//           numConsume);
//    createProducers2(input, size, numProduce);
//    treeTime = doBSTv3(sortedInput, size, numConsume, which);
//    joinProducers2();
//    printf("Time: %f sec\n", treeTime);
//
//    printf("\nBuilding trees with %d threads and no locks.\n", numConsume);
//    createProducers2(input, size, numProduce);
//    treeTime = doBSTv4(sortedInput, size, numConsume, which);
//    joinProducers2();
//    printf("Time: %f sec\n", treeTime);

}

/*
 * getArgs
 * Parse the command line arguments to get the number of values
 * to insert into the BST, the number of consumer threads, and the
 * number of producer threads.
 * argc - number of command line arguments
 * argv - array of command line arguments
 * size - pointer to int to be set to the number of values
 *        to be inserted into the BST
 * numConsume - pointer to int to be set to the number of consumer
 *        threads to get a value from the producer-consumer buffer and
 *        insert into a BST
 * numProduce - pointer to the int to be set to the number of
 *        producer threads to fill the producer-consumer buffer
 */
void getArgs(int argc, char * argv[], int * size,
             int * numConsume, int * numProduce)
{
   char opt;
   (*size) = SIZE_DEFAULT;
   (*numConsume) = NUMCONSUME_DEFAULT;
   (*numProduce) = NUMPRODUCE_DEFAULT;
   while((opt = getopt(argc, argv, "s:c:p:h")) != -1)
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
         case 's':
            (*size) = atoi(optarg);
            if ((*size) <= 0)
            {
               fprintf(stderr, "bad -s option: Number of ");
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

/*
 * printUsage
 * Print the usage information and exit
 */
void printUsage()
{
   printf("usage: ./bst [-s <size>] [-c <cthreads>] [-p <pthreads> ] [ -h ] \n");
   printf("       <size> is the number of nodes to insert\n");
   printf("              default: %d\n", SIZE_DEFAULT);
   printf("       <cthreads> is the number of consumer threads to use\n");
   printf("              default: %d\n", NUMCONSUME_DEFAULT);
   printf("       <threads> is the number of producer threads to use\n");
   printf("              default: %d\n", NUMPRODUCE_DEFAULT);
   printf("       -h print usage info and exit\n");
   exit(1);
}

/*
 * makeInput
 * Randomly generates size numbers within the range
 * 0 and (size * 2)-1 [inclusive]. Fills the nums array
 * with those values.
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

/*
 * sortInput
 * sort the nums array using an insertion sort
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


