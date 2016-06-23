/* Copyright (c) 2013, Colfax International. All Right Reserved.
file matrix.cpp, located at 2/2.4-explicit-offload-matrix/step-05
is a part of the practical supplement to the handbook
"Parallel Programming and Optimization with Intel Xeon Phi Coprocessors" 
(c) Colfax International, 2013, ISBN: 978-0-9885234-1-8
Redistribution or commercial usage without a written permission 
from Colfax International is prohibited.
Contact information can be found at http://colfax-intl.com/     */

#include <stdio.h>
#include <stdlib.h>

// use `ulimit -s unlimited` to increase the stack size for the process
// Otherwise, code will be stopped with the "segmentation fault" error

int main(){
    
    const int iterMax = 3;
    const int m=1000, n=100000;
    double b[n], c_target[m], c_host[m];
    double * A = (double*) malloc(sizeof(double)*n*m);
    const double worksplit = 0.7;

    // Cilk Plus array notation
    A[0:n*m]=1.0/(double)n;

    #pragma offload_transfer target(mic:1) in (A:length(n*m) free_if(0))

    for ( int iter = 0; iter < iterMax ; iter++) {
        b[:] = (double) iter;
        c_target[:]=0; // results calculated on the coprocessor
        c_host[:]=0; // results calculated on the host

        #pragma offload target(mic:1) nocopy(A : free_if(iter==iterMax-1)) \
             signal(A)
        {
        // running the calculation on the coprocessor asynchronously
            int ilo = 0;
            int ihi = (int) (worksplit*m);
            for ( int i = ilo ; i < ihi ; i++)
                for ( int j = 0 ; j < n ; j++)
                    c_target [i] += A[i*n+j] * b[j];
        }

        // the following code is running on the host asynchronously 
		{
			int ilo = (int) (worksplit*m);
			int ihi = m;
			for ( int i = ilo ; i < ihi ; i++)
				for ( int j = 0 ; j < n ; j++)
					c_host[i] += A[i*n+j] * b[j];
		}
        // sync before proceeding
        #pragma offload_transfer target(mic:1) out(c) wait(A)

        // combine
		{
			int ilo = 0;
			int ihi = (int) (worksplit*m);
			for ( int i = ilo ; i < ihi ; i++)
				c_host [i] = c_target[i];
		}

        double norm = 0.0;
        for ( int i = 0 ; i < m ; i++)
            norm += (c_target[i] - c_host[i])*(c_target[i] - c_host[i]);
            printf("Difference is %e: ", norm);
        if (norm > 1e-10)
            printf("ERROR!\n");
        else
            printf("Yep, we're good!\n");
    }
}
