#include <stdio.h>
#include <mpi.h>
#include <omp.h>

int main (argc, argv)
     int argc;
     char *argv[];
{
        int rank, size;
        int nthreads, tid;
        MPI_Init (&argc, &argv);        /* starts MPI */
        MPI_Comm_rank (MPI_COMM_WORLD, &rank);  /* get current process id */
        MPI_Comm_size (MPI_COMM_WORLD, &size);  /* get number of processes */


        printf( "Hello from HOST process %d of %d\n", rank, size );

        #pragma omp parallel private(nthreads, tid)
        {
                tid=omp_get_thread_num();
                nthreads=omp_get_num_threads();
                printf("Hello from HOST thread %d on process %d\n", tid, rank);
        #pragma omp barrier
                if (tid == 0)
                {
                        printf("\n-----------------------------------------------------------\n");
                        printf("Number of HOST threads used = %d on process %d\n",nthreads, rank);
                        printf("Max HOST threads available  = %d on process %d\n",omp_get_max_threads(), rank);
                        printf("-----------------------------------------------------------\n\n");

                }

        }

/* Offload to an Intel Xeon Phi */
#pragma offload target(mic)
{
        /* Fork a team of threads giving them their own copies of variables */
        #pragma omp parallel private(nthreads, tid)
        {

                /* Obtain thread number */
                tid = omp_get_thread_num();
                printf("Hello from XeonPhi thread = %d\n", tid);
        #pragma omp barrier 
                /* Only master thread does this */
                if (tid == 0)
                {
                        nthreads = omp_get_num_threads();
                        printf("\n-----------------------------------------------------------\n");
                        printf("Number of XeonPhi threads used = %d\n", nthreads);
                        printf("Max Xeon Phi threads available = %d on process %d\n",omp_get_max_threads(), rank);
                        printf("-----------------------------------------------------------\n");
                }

        }  /* All threads join master thread and disband */
} /* End Xeon Phi offload region */



  MPI_Finalize();
  return 0;
}

