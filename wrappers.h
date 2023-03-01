#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

void * Malloc(size_t size);
void Pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                    void *(*start_routine) (void *), void *arg);
void Pthread_join(pthread_t thread, void **retval);

