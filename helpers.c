#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

//compare the values in correctValues to the
//values and bstValues to see if they match
void compare(int * correctValues, int * bstValues, int size)
{
   int i;
   for (i = 0; i < size; i++)
   {
      if (correctValues[i] != bstValues[i])
      {
         printf("Error at index %d: correct value is %d, bst value is %d\n",
                i, correctValues[i], bstValues[i]);
         exit(1);
      }
   }
}

//prints out the elements of an array
//potentially useful for debugging
void printNums(int * nums, int size)
{
   int i;
   for (i = 0; i < size; i++)
   {
      if ((i % 10) == 0) printf("\n");
      printf("%d ", nums[i]);
   }
}

