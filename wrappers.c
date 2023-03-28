#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

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

/*
 * Pthread_mutex_destroy
 * The  pthread_mutex_destroy() function shall destroy the mutex object
 * referenced by mutex; the mutex object becomes, in effect, uninitialized.
 * If successful, the pthread_mutex_destroy() function returns 0;
 * otherwise, an error number shall be returned to indicate the error.
 * mutex - pointer to pthread_mutex_t object
 */
void Pthread_mutex_destroy(pthread_mutex_t *mutex)
{
   int succ = pthread_mutex_destroy(mutex);
   if (succ != 0)
   {
      printf("pthread_mutex_destroy failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}

/* Pthread_mutex_init
 * The pthread_mutex_init() function shall initialize the mutex
 * referenced by mutex with attributes specified by attr. If attr is NULL,
 * the default mutex attributes are used.
 * If successful, the pthread_mutex_init() function returns 0;
 * otherwise, an error number shall be returned to indicate the error.
 * mutex - pointer to pthread_mutex_t object
 * attr - pointer to attributes object
 */
void Pthread_mutex_init(pthread_mutex_t * mutex,
                        const pthread_mutexattr_t * attr)
{
   int succ = pthread_mutex_init(mutex, attr);
   if (succ != 0)
   {
      printf("pthread_mutex_init failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}

/*
 * Pthread_mutex_lock
 * The mutex object referenced by mutex shall be locked by calling
 * pthread_mutex_lock(). If the mutex is already locked, the calling thread shall
 * block until the mutex becomes available. This operation shall return with
 * the mutex object referenced by mutex in the locked state with the calling
 * thread as its owner.
 * If successful, the pthread_mutex_lock() function shall return zero;
 * otherwise, an error number shall be returned to indicate the error.
 * mutex - pointer to pthread_mutex_t object
 */
void Pthread_mutex_lock(pthread_mutex_t *mutex)
{
   int succ = pthread_mutex_lock(mutex);
   if (succ != 0)
   {
      printf("pthread_mutex_lock failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}

/*
 * Pthread_mutex_unlock
 * The pthread_mutex_unlock() function shall release the mutex object
 * referenced by mutex. The manner in which a mutex is released is
 * dependent upon the mutex's type attribute. If there are threads
 * blocked on the mutex object referenced by mutex when pthread_mutex_unlock()
 * is called, resulting in the mutex becoming available, the scheduling policy
 * shall determine which thread shall acquire the mutex.
 * If successful, the pthread_mutex_unlock() function shall return zero;
 * otherwise, an error number shall be returned to indicate the error.
 * mutex - pointer to pthread_mutex_t object
 */
void Pthread_mutex_unlock(pthread_mutex_t *mutex)
{
   int succ = pthread_mutex_unlock(mutex);
   if (succ != 0)
   {
      printf("pthread_mutex_unlock failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}

/*
 * Pthread_cond_init
 * The pthread_cond_init() function shall initialize the condition variable
 * referenced by cond with attributes referenced by attr. If attr is
 * NULL, the default condition variable  attributes  shall  be  used.
 * If successful, the pthread_cond_init() function shall return zero;
 * otherwise, an error number shall be returned to indicate the error.
 * cond - pointer to the condition variable to be initialized
 * attr - pointer to an object containing the attributes to be used
 *        in the initialization
 */
void Pthread_cond_init(pthread_cond_t * cond,
                       const pthread_condattr_t * attr)
{
   int succ = pthread_cond_init(cond, attr);
   if (succ != 0)
   {
      printf("pthread_cond_init failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}

/*
 * Pthread_cond_destroy
 * The  pthread_cond_destroy() function shall destroy the given condition
 * variable specified by cond; the object becomes, in effect, uninitialized.
 * If successful, the pthread_cond_destroy() function shall return zero;
 * otherwise, an error number shall be returned to indicate the error.
 * cond - pointer to the condition variable to be destroyed
 */
void Pthread_cond_destroy(pthread_cond_t * cond)
{
   int succ = pthread_cond_destroy(cond);
   if (succ != 0)
   {
      printf("pthread_cond_destroy failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}

/*
 * Pthread_cond_signal
 * The pthread_cond_signal() function shall unblock at least one of the threads
 * that are blocked on the specified condition variable cond (if any threads are
 * blocked on cond).
 * If  successful, the pthread_cond_signal() function shall return zero;
 * otherwise, an error number shall be returned to indicate the error.
 * cond - pointer to the condition variable to be used for the signal
 */
void Pthread_cond_signal(pthread_cond_t * cond)
{
   int succ = pthread_cond_signal(cond);
   if (succ != 0)
   {
      printf("pthread_cond_signal failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}

/*
 * Pthread_cond_wait
 * The pthread_cond_wait() function shall block on a condition variable.
 * The function atomically releases mutex and causes the calling thread
 * to  block on the condition variable cond.
 * Upon successful  completion, a value of zero shall be returned;
 * otherwise, an error number shall be returned to indicate the error.
 * cond - pointer to the condition variable to be blocked on
 * mutex - pointer to the mutex released when the blocking occurs
*/
void Pthread_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex)
{
   int succ = pthread_cond_wait(cond, mutex);
   if (succ != 0)
   {
      printf("pthread_cond_wait failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }

}

/*
 * Sem_post
 * sem_post() increments (unlocks) the semaphore pointed to by sem.
 * If the semaphore's value consequently becomes greater than zero,
 * then another process or thread blocked in a sem_wait() call
 * will be woken up and proceed to lock the semaphore.
 * sem_post() returns 0 on success; on error, the value of the semaphore
 * is left unchanged, -1 is returned, and errno is set to indicate
 * the error.
 * sem - pointer to the semaphore that is incremented
*/
void Sem_post(sem_t * sem)
{
   int succ = sem_post(sem);
   if (succ != 0)
   {
      printf("sem_post failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}

/*
 * Sem_wait
 * sem_wait() decrements (locks) the semaphore pointed to by sem.
 * If the semaphore's value is greater than zero, then the
 * decrement proceeds, and the function returns, immediately.
 * This function returns 0 on success; on error, the value of
 * the semaphore is left unchanged, -1 is returned, and errno is
 * set to indicate the error.
 * sem - pointer to the semaphore that is decremented
 */
void Sem_wait(sem_t * sem)
{
   int succ = sem_wait(sem);
   if (succ != 0)
   {
      printf("sem_wait failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}

/*
 * Sem_destroy
 * sem_destroy() destroys the unnamed semaphore at the
 * address pointed to by sem.
 * This function returns 0 on success; on error, the value of
 * the semaphore is left unchanged, -1 is returned, and errno is
 * set to indicate the error.
 * sem - pointer to the semaphore that is destroyed
 */
void Sem_destroy(sem_t * sem)
{
   int succ = sem_destroy(sem);
   if (succ != 0)
   {
      printf("sem_destroy failed: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
}
