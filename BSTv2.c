#include <stdlib.h>
#include "helpers.h"
#include "macros.h"
#include <pthread.h>
#include "wrappers.h"
#include <semaphore.h>
#include "producerConsumer1.h"
#include "producerConsumer2.h"
#include "BSTversions.h"

// BST node structure
typedef struct BSTv2 {
    int val;
    struct BSTv2* left;
    struct BSTv2* right;
}BSTv2_t;

// Struct for thread data
typedef struct insert_data {
    int *input;
    int start;
    int end;
} insert_data_t;

// Global BST root and lock
static BSTv2_t* root = NULL;
pthread_mutex_t tree_lock = PTHREAD_MUTEX_INITIALIZER;

//functions for creating nodes
static BSTv2_t * createNode(int value);
static void BSTv2Insert(int value);
static void * doInsert(void * arg);
static void inorder(BSTv2_t * ptr, int * array);
static void BSTv2GetNums(int * array);

//create a node to insert in the tree
BSTv2_t * createNode(int value)
{
   BSTv2_t *newNode = (BSTv2_t *)Malloc(sizeof(BSTv2_t));
   newNode->val = value;
   newNode->left = NULL;
   newNode->right = NULL;

   return newNode;
}


void BSTv2Insert(int value)
{
   BSTv2_t * ptr = root; //root of tree
   //insert the value into the tree
   if(root == NULL)
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

// Insert a value into the BST with a lock
void * doInsert(void *arg)
{
   int i;
   int which = *(int*)arg;
   /*while((i = consume1())!= -1)
   {
      Pthread_mutex_lock(&tree_lock);
      BSTv2Insert(i);
      Pthread_mutex_unlock(&tree_lock);
   }*/
   if (which == PC1) {
      while((i = consume1()) != -1) {
         //insert each value
         Pthread_mutex_lock(&tree_lock);
         BSTv2Insert(i);
         Pthread_mutex_unlock(&tree_lock);
      }
   }
   else if (which == PC2) {
      while((i = consume2())!= -1){
         Pthread_mutex_lock(&tree_lock);
         BSTv2Insert(i);
         Pthread_mutex_unlock(&tree_lock);
      }
   }
    return NULL;
}


//Build the BST using just numThreads threads and one lock per tree. 
//Check for correctness.
//Return the time it takes to do it.
//double doBSTv2(int * input, int * sortedInput, int size, int numThreads)
double doBSTv2(int * sortedInput, int size, int numThreads, int which)
{
   int treeValues[size];
   int i;
  
   // Initialize global lock
   pthread_mutex_init(&tree_lock, NULL);
  
   TIMERSTART(BSTV2)
   pthread_t threads[numThreads];
   for(i = 0; i< numThreads; i++){
      int* whichPtr = (int*)Malloc(sizeof(int));
      *whichPtr = which;
      Pthread_create(&threads[i], NULL, doInsert, whichPtr);
   }

   // unlock tree after all threads are done
   for (i = 0; i < numThreads; i++) {
        Pthread_join(threads[i], NULL);

    }


   //get the values
   BSTv2GetNums(treeValues);

   TIMERSTOP(BSTV2)   
   double treeTime = DURATION(BSTV2)

   //check for correctness
   compare(sortedInput, treeValues, size);
   return treeTime;
}

void BSTv2GetNums(int * array)
{
   inorder(root, array);
}

//traversal of the tree
void inorder(BSTv2_t * ptr, int * array)
{
   static int i = 0;
   if(ptr == NULL)
   {
      return;
   }
   inorder(ptr->left, array);
   array[i++] = ptr->val;
   inorder(ptr->right, array);
}

