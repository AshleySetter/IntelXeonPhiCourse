#include <stdio.h>
#include <omp.h>

void testThreads();

int main(int argc,char **argv)
{
  testThreads();
  return 0;
}

void testThreads()
{
        int tCount,threadsMax,tid;
#ifdef __MIC__
        printf("Running on Xeon Phi\n---------------\n");
#else
        printf("Running on HOST\n---------------\n");
#endif //__MIC__

        threadsMax=omp_get_max_threads();
        #pragma omp parallel default(none) private(tid) shared(tCount,threadsMax)
        {
                tid = omp_get_thread_num();
        #pragma omp critical
        printf("Hello from thread %d\n",tid);
        #pragma omp barrier 
        #pragma omp master
        {
                tCount = omp_get_num_threads();
                printf("Total number of threads used is %d\n", tCount);
                printf("Maximum number of threads available is %d\n", threadsMax);
                printf("================================\n");
        }
  }
}

