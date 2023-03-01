#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "BSTversions.h"

//static makes these local to this file
static void makeInput(int * nums, int size);
static void sortInput(int * nums, int size);
static void getArgs(int argc, char * argv[], int * size, int * numThreads);
static void printUsage();

//default tree size and default number of threads
#define SIZE_DEFAULT 1000
#define NUMTHREADS_DEFAULT 4

int main(int argc, char * argv[])
{
   int size;
   int numThreads;
   getArgs(argc, argv, &size, &numThreads);

   int * input = malloc(sizeof(int) * size);
   int * sortedInput = malloc(sizeof(int) * size);
   double treeTime;

   //randomly generate some input
   makeInput(input, size);
   memcpy(sortedInput, input, sizeof(int) * size);
   printf("Sorting the input to check for correctness (n = %d).\n",
          size);
   //sort the input to check for correctness
   sortInput(sortedInput, size);

   printf("\nBuilding trees with 1 thread.\n");
   treeTime = doBSTv1(input, sortedInput, size);
   printf("Time: %f sec\n", treeTime);

   printf("\nBuilding trees with %d threads and one lock per thread.\n", numThreads);
   treeTime = doBSTv2(input, sortedInput, size, numThreads);
   printf("Time: %f sec\n", treeTime);

   printf("\nBuilding trees with %d threads and one lock per node.\n", numThreads);
   treeTime = doBSTv3(input, sortedInput, size, numThreads);
   printf("Time: %f sec\n", treeTime);

   printf("\nBuilding trees with %d threads and no locks.\n", numThreads);
   treeTime = doBSTv4(input, sortedInput, size, numThreads);
   printf("Time: %f sec\n", treeTime);

   return 0;
}

//parse command line arguments to get the
//tree size and the number of threads to use
void getArgs(int argc, char * argv[], int * size, int * numThreads)
{
   char opt;
   (*size) = SIZE_DEFAULT;
   (*numThreads) = NUMTHREADS_DEFAULT;
   while((opt = getopt(argc, argv, "s:t:")) != -1)
   {
      switch (opt)
      {
         case 't':
            (*numThreads) = atoi(optarg);
            if ((*numThreads) <= 1)
            {
               fprintf(stderr, "bad -t option: Number of ");
               fprintf(stderr, "threads needs to be > 1\n");
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
         case '?':
            printUsage();
      }
   }
}

//print the usage information and exit
void printUsage()
{
   printf("usage: ./bst [-s <size>] [-t <threads>]\n");
   printf("       <size> is the number of nodes to insert\n");
   printf("              default: %d\n", SIZE_DEFAULT);
   printf("       <threads> is the number of threads to use\n");
   printf("              default: %d\n", NUMTHREADS_DEFAULT);

   exit(1);
}

//randomly generate input to use
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

//sort the nums using an insertion sort     
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

