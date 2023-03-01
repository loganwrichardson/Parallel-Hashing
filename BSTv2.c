#include <stdlib.h>
#include "helpers.h"
#include "macros.h"

//Build the BST using just numThreads threads and one lock per tree. 
//Check for correctness.
//Return the time it takes to do it.
double doBSTv2(int * input, int * sortedInput, int size, int numThreads)
{
   int treeValues[size];

   TIMERSTART(BSTV2)


   TIMERSTOP(BSTV2)   
   double treeTime = DURATION(BSTV2)

   //check for correctness
   compare(sortedInput, treeValues, size);
   return treeTime;
}
