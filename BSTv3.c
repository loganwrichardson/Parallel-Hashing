#include <stdlib.h>
#include "helpers.h"
#include "macros.h"
#include <pthread.h>
#include "wrappers.h"
#include <semaphore.h>
#include "producerConsumer1.h"
#include "BSTversions.h"


// BST node structure
typedef struct BSTv3
{
   int val;
   struct BSTv3 * left;
   struct BSTv3 * right;
   pthread_mutex_t lock;
}BSTv3_t;

typedef struct insert_data {
    int *input;
    int start;
    int end;
} insert_data_t;

//Global BST root
static BSTv3_t * root = NULL;
pthread_mutex_t root_lock = PTHREAD_MUTEX_INITIALIZER;

//functions for creating node
static BSTv3_t * createNode(int value);
static void BSTv3Insert(int value);
static void * doInsert(void * arg);
static void inorder(BSTv3_t * ptr, int * array);
static void BSTv3GetNums(int * array);

//create a node to insert in the tree
BSTv3_t * createNode(int value)
{
   BSTv3_t *newNode = (BSTv3_t *)Malloc(sizeof(BSTv3_t));
   newNode->val = value;
   newNode->left = NULL;
   newNode->right = NULL;
   pthread_mutex_init(&(newNode->lock), NULL); // initialize lock for the new node
   return newNode;
}
void BSTv3Insert(int value)
{
   BSTv3_t * ptr = root; // root of tree
   BSTv3_t * prev = ptr; // previous node visited
   pthread_mutex_lock(&root_lock); // lock the root node
   if (root == NULL) {
      root = createNode(value);
      pthread_mutex_unlock(&root_lock); // unlock the root node
      return;
   }
   pthread_mutex_lock(&(ptr->lock)); // lock the root node
   pthread_mutex_unlock(&root_lock); // unlock the root node
   while (1)
   {
      if (value < ptr->val)
      {
         if(ptr->left == NULL)
         {
            ptr->left = createNode(value);
            pthread_mutex_unlock(&(ptr->lock)); // unlock the node
            return;
         }
         else
         {
            pthread_mutex_lock(&(ptr->left->lock)); // lock the left child
            pthread_mutex_unlock(&(ptr->lock)); // unlock the node
            prev = ptr; // update previous node
            ptr = ptr->left; // move to the left child
         }
      }
      else
      {
         if(ptr->right == NULL)
         {
            ptr->right = createNode(value);
            pthread_mutex_unlock(&(ptr->lock)); // unlock the node
            if (prev != NULL) {
              pthread_mutex_unlock(&(prev->lock)); // unlock previous node
            }
            return;
         }
         else
         {
            pthread_mutex_lock(&(ptr->right->lock)); // lock the right child
            pthread_mutex_unlock(&(ptr->lock)); // unlock the node
            prev = ptr; // update previous node
            ptr = ptr->right; // move to the right child
         }
      }
   }
}

// function for inserting nodes in the tree
void * doInsert(void * arg)
{
   int i;
   int which = *(int*)arg;
   /*while((i = consume1())!= -1)
   {
      //insert each value
      BSTv3Insert(i);
   }*/
   if (which == PC1) {
      while((i = consume1()) != -1) {
         //insert each value
         BSTv3Insert(i);
      }
   }
   else if (which == PC2) {
       /*while((i = consume2())!= -1){
         BSTv3Insert(i);*/
   }
   
   return NULL;
}

//Build the BST using just numThreads threads and one lock per node. 
//Check for correctness.
//Return the time it takes to do it.
//double doBSTv3(int * input, int * sortedInput, int size, int numThreads)
double doBSTv3(int * sortedInput, int size, int numThreads, int which)
{
   int i;
   int treeValues[size];

   TIMERSTART(BSTV3)

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

   pthread_mutex_lock(&root_lock); // lock the root node
   BSTv3GetNums(treeValues);
   pthread_mutex_unlock(&root_lock); // unlock the root node


   TIMERSTOP(BSTV3)   
   double treeTime = DURATION(BSTV3)

   //check for correctness
   compare(sortedInput, treeValues, size);
   return treeTime;
}

void BSTv3GetNums(int * array)
{
   inorder(root, array);
}


//traversal of the tree
void inorder(BSTv3_t * ptr, int * array)
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