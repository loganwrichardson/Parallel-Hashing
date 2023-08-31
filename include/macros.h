#include <time.h>

#define BILLION  1000000000L

#define CHANNELS 3

#define TIMERSTART(label)                         \
    struct timespec start##label, stop##label;    \
    clock_gettime(CLOCK_REALTIME, &start##label); 

#define TIMERSTOP(label)                          \
    clock_gettime(CLOCK_REALTIME, &stop##label); 

#define DURATION(label)                           \
    (stop##label.tv_sec - start##label.tv_sec) +  \
    ((double)(stop##label.tv_nsec - start##label.tv_nsec) / BILLION); 

