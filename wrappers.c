#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#include "wrappers.h"

/* 
 * Malloc
 * wrapper for the malloc function
 * If malloc returns NULL then the memory allocation failed.
 *
*/
void * Malloc(size_t size)
{
   void * allocData = (void *) malloc(size);
   if (allocData == NULL)
   {
      printf("malloc failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
   return allocData;
}

/*
 * Pthread_create
 * Starts a new thread in the calling process.  
 * 
 * thread - pointer to a pthread_t variable that is set to the thread identifier
 *          of the thread that is created (needed for joining)
 * attr - points to a structure that contains attributes for the thread
 *        (NULL is fine for this assignment)
 * start_routine - routine to be executed in the thread
 * arg - sole argument to the thread 
 *       (commonly, we package arguments up in a struct and pass a pointer to it)
 * See examples supplied in book and slides on how to use this
 */
void Pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                    void *(*start_routine) (void *), void *arg)
{
   int succ = pthread_create(thread, attr, start_routine, arg);
   if (succ != 0)
   {
      printf("pthread_create failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}

/*
 * Pthread_join
 * The pthread_join() function waits for the thread specified by thread to
 * terminate.  If that thread has already terminated, then  pthread_join()
 * returns immediately.
 * See examples supplied in book and slides on how to use this
 * thread - thread identifier
 * retval - pointer to location to be set to the exit status of the thread; ie.
 *          the value supplied by pthread_exit (NULL works for this assignment)
 */
void Pthread_join(pthread_t thread, void **retval)
{
   int succ = pthread_join(thread, retval);
   if (succ != 0)
   {
      printf("pthread_join failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}
