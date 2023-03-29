#include <stdlib.h>
#include "helpers.h"
#include "macros.h"
#include "wrappers.h"
#include <semaphore.h>
#include "producerConsumer1.h"
#include "producerConsumer2.h"
#include "BSTversions.h"

// BST node structure
typedef struct BSTv4_t {
   int val;
   struct BSTv4_t * left;
   struct BSTv4_t * right;
} BSTv4_t;

//Global initialization
static BSTv4_t * root = NULL;
static int array_index = 0;

//functions for creating bst
static BSTv4_t * createNode(int value);
static void inorder(BSTv4_t * ptr, int * array);
static void BSTv4Insert(int value);
static void BSTv4GetNums(int * array);
static void * doInsert(void * arg);
static void resetBSTv4();

//function to create node
BSTv4_t * createNode(int value)
{
   BSTv4_t * node = (BSTv4_t *)malloc(sizeof(BSTv4_t));
   node->val = value;
   node->left = NULL;
   node->right = NULL;
   return node;
}

//function to insert value 
void BSTv4Insert(int value)
{
   BSTv4_t * node = root;
   BSTv4_t * newNode;

   newNode = createNode(value);

   //insert the value into the tree
   if (root == NULL)
   {
     if (__sync_bool_compare_and_swap(&root, NULL, newNode))
         return;
      else
         free(newNode);
   }
   
   while (1)
   {
      if (value < node->val)
      {
         if (node->left == NULL)
         {
            if (__sync_bool_compare_and_swap(&(node->left), NULL, newNode))
              return;
         }
         else
            node = node->left;
      }
      else
      {
         if (node->right == NULL)
         {
            if (__sync_bool_compare_and_swap(&(node->right), NULL, newNode))
               return;
         }
         else
            node = node->right;
      }
   }
}

// function for inserting nodes in the tree
void * doInsert(void * arg)
{
   int i;
   int which = *(int*)arg;
   if (which == PC1) {
      while((i = consume1()) != -1) {
         //insert each value
         BSTv4Insert(i);
      }
   }
   else if (which == PC2) {
      while((i = consume2())!= -1){
         BSTv4Insert(i);
      }
   }
   
   return NULL;
}


//Build the BST using just numThreads threads and no lock. 
//Check for correctness.
//Return the time it takes to do it.
//double doBSTv4(int * input, int * sortedInput, int size, int numThreads)
double doBSTv4(int * sortedInput, int size, int numThreads, int which)
{
   int treeValues[size];

   resetBSTv4();

   TIMERSTART(BSTV4)

   int i;
   pthread_t threads[numThreads];
   for (i = 0; i < numThreads; i++)
   {
      int* whichPtr = (int*)Malloc(sizeof(int));
      *whichPtr = which;
      Pthread_create(&threads[i], NULL, doInsert, whichPtr);
   }
   
   for (i = 0; i < numThreads; i++)
   {
      Pthread_join(threads[i], NULL);
   }


   //get the values
   BSTv4GetNums(treeValues);

   TIMERSTOP(BSTV4)   
   double treeTime = DURATION(BSTV4)

   //check for correctness
   compare(sortedInput, treeValues, size);
   return treeTime;
}

// function to reset the static variable 
void resetBSTv4(){
   root = NULL;
   array_index = 0;
}

//function for getting values 
void BSTv4GetNums(int * array)
{
   inorder(root, array);
}


//traversal of the tree
void inorder(BSTv4_t * ptr, int * array)
{
   if(ptr == NULL)
   {
      return;
   }
   inorder(ptr->left, array);
   array[array_index++] = ptr->val;
   inorder(ptr->right, array);
}

