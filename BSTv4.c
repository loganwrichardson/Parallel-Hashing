#include <stdlib.h>
#include "helpers.h"
#include "macros.h"

//Build the BST using just numThreads threads and no lock. 
//Check for correctness.
//Return the time it takes to do it.
double doBSTv4(int * input, int * sortedInput, int size, int numThreads)
{
   int treeValues[size];

   TIMERSTART(BSTV4)


   TIMERSTOP(BSTV4)   
   double treeTime = DURATION(BSTV4)

   //check for correctness
   compare(sortedInput, treeValues, size);
   return treeTime;
}
