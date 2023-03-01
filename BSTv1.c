#include <stdlib.h>
#include "helpers.h"
#include "macros.h"

struct BSTv1
{
   int val;
   struct BSTv1 * left;
   struct BSTv1 * right;
};
typedef struct BSTv1 BSTv1_t;

//static means these aren't accessible outside of this file
static BSTv1_t * root = NULL; //pointer to root

//functions for creating nodes
static BSTv1_t * createNode(int value);
static void inorder(BSTv1_t * ptr, int * array);
static void BSTv1Insert(int value);
static void BSTv1GetNums(int * array);

//Build the BST using just one thread (the calling thread). 
//Check for correctness.
//Return the time it takes to do it.
double doBSTv1(int * input, int * sortedInput, int size)
{
   int i;
   int treeValues[size];

   TIMERSTART(BSTV1)

   for (i = 0; i < size; i++)
   {
      //insert each value
      BSTv1Insert(input[i]);
   }
   //get the values
   BSTv1GetNums(treeValues);

   TIMERSTOP(BSTV1)   
   double treeTime = DURATION(BSTV1)

   //check for correctness
   compare(sortedInput, treeValues, size);
   return treeTime;
}

//insert the value into the tree
//root declared at the top is the pointer to
//root node of the tree (initially NULL)
void BSTv1Insert(int value)
{
   //TODO
   BSTv1_t * ptr = root; //root of tree
}

//create a node to insert in the tree
BSTv1_t * createNode(int value)
{
   //TODO
   return NULL;
}

//get the nodes in the tree by doing an inorder traversal
void BSTv1GetNums(int * array)
{
   inorder(root, array);
}

//fill the nodes of the array performing an inorder
//traversal of the tree
void inorder(BSTv1_t * ptr, int * array)
{
   //TODO
}
