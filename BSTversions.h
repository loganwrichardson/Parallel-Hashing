/*double doBSTv1(int * input, int * sortedInput, int size);
double doBSTv2(int * input, int * sortedInput, int size, int numThreads);
double doBSTv3(int * input, int * sortedInput, int size, int numThreads);
double doBSTv4(int * input, int * sortedInput, int size, int numThreads);*/

//Producer-Consumer Version 1 (uses semaphores)
#define PC1 1
//Producer-Consumer Version 2 (uses condition variables)
#define PC2 2
//last parameter to each of these indicates which version
//of the Producer-Consumer to use
//if which is PC1 then consume1 is called.
//if which is PC2 then consume2 is called.
double doBSTv1(int * sortedInput, int size, int which);
double doBSTv2(int * sortedInput, int size, int numThreads, int which);
double doBSTv3(int * sortedInput, int size, int numThreads, int which);
double doBSTv4(int * sortedInput, int size, int numThreads, int which);

