#include <stdlib.h>
#include <semaphore.h>
#include "helpers.h"
#include "macros.h"
#include "wrappers.h"
#include "producerConsumer1.h"
#include "producerConsumer2.h"
#include "BSTversions.h"

struct BSTv1
{
   int val;
   struct BSTv1 * left;
   struct BSTv1 * right;
};
typedef struct BSTv1 BSTv1_t;

//static means these aren't accessible outside of this file
static BSTv1_t * root = NULL; //pointer to root
static int array_index  = 0;

//functions for creating nodes
static BSTv1_t * createNode(int value);
static void inorder(BSTv1_t * ptr, int * array);
static void BSTv1Insert(int value);
static void BSTv1GetNums(int * array);
static void resetBSTv1();

//Build the BST using just one thread (the calling thread). 
//Check for correctness.
//Return the time it takes to do it.
//double doBSTv1(int * input, int * sortedInput, int size)
double doBSTv1(int * sortedInput, int size, int which)
{
   int i;
   int treeValues[size];
   resetBSTv1();

   TIMERSTART(BSTV1)

   /*while((i = consume1())!= -1)
   {
      //insert each value
      BSTv1Insert(i);
   }*/
   if (which == PC1) {
      while((i = consume1()) != -1) {
         //insert each value
         BSTv1Insert(i);
      }
   }
   else if (which == PC2) {
       while((i = consume2()) != -1){
         BSTv1Insert(i);
      }
   }


   //get the values

   BSTv1GetNums(treeValues);
    

   TIMERSTOP(BSTV1)   
   double treeTime = DURATION(BSTV1)

   //check for correctness
   compare(sortedInput, treeValues, size);
   return treeTime;
}

void resetBSTv1() {
   root = NULL;
   array_index = 0;
}
//insert the value into the tree
//root declared at the top is the pointer to
//root node of the tree (initially NULL)
void BSTv1Insert(int value)
{
   BSTv1_t * ptr = root; //root of tree

   //insert the value into the tree
   if (root == NULL)
   {
      root = createNode(value);
      return;
   }

  while (1)
   {
      if (value < ptr->val)
      {
         if(ptr->left == NULL)
         {
            ptr->left = createNode(value);
            return;
         }
         else
         {
            ptr = ptr->left;
         }
      }
      else
      {
         if(ptr->right == NULL)
         {
            ptr->right = createNode(value);
            return;
         }
         else
         {
            ptr = ptr->right;
         }
      }
   }
}

//create a node to insert in the tree
BSTv1_t * createNode(int value)
{
   //TODO
   BSTv1_t *newNode = (BSTv1_t *)Malloc(sizeof(BSTv1_t));
   newNode->val = value;
   newNode->left = NULL;
   newNode->right = NULL;

   return newNode;
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
   if(ptr == NULL)
   {
      return;
   }
   inorder(ptr->left, array);
   array[array_index++] = ptr->val;
   inorder(ptr->right, array);
}
