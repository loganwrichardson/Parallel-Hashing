#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

void * Malloc(size_t size);

void Pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

void Pthread_join(pthread_t thread, void **retval);

void Pthread_mutex_destroy(pthread_mutex_t *mutex);

void Pthread_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t *  attr);

void Pthread_mutex_lock(pthread_mutex_t *mutex);

void Pthread_mutex_unlock(pthread_mutex_t *mutex);

void Pthread_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);

void Pthread_cond_destroy(pthread_cond_t * cond);

void Pthread_cond_signal(pthread_cond_t * cond);

void Pthread_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);

void Sem_post(sem_t * sem);

void Sem_wait(sem_t * sem);

void Sem_destroy(sem_t * sem);
