#include <stdlib.h>
#include "helpers.h"
#include "macros.h"

//Build the BST using just numThreads threads and one lock per node. 
//Check for correctness.
//Return the time it takes to do it.
double doBSTv3(int * input, int * sortedInput, int size, int numThreads)
{
   int treeValues[size];

   TIMERSTART(BSTV3)


   TIMERSTOP(BSTV3)   
   double treeTime = DURATION(BSTV3)

   //check for correctness
   compare(sortedInput, treeValues, size);
   return treeTime;
}
