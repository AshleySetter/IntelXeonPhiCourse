/* Copyright (c) 2013, Colfax International. All Right Reserved.
file matrix.cpp, located at 2/2.4-explicit-offload-matrix/step-03
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
    
    const int m=1000, n=100000;
    const int maxIter = 5;
    double b[n], c[m];
    double * A = (double*) malloc(sizeof(double)*n*m);

    // Cilk Plus array notation
    A[0:n*m]=1.0/(double)n;
    b[:]=1.0;
    c[:]=0;

    #pragma offload_transfer target(mic:0) in (A:length(n*m) free_if(0))

    for ( int iter = 0; iter < maxIter ; iter++) {

        printf("Iteration %d of %d...\n", iter+1, maxIter);

        b[:] = (double) iter;

        #pragma offload target(mic:0) nocopy (A:length(n*m) free_if(iter==maxIter-1))
        {
        for ( int i = 0 ; i < m ; i++)
            for ( int j = 0 ; j < n ; j++)
                c[i] += A[i*n+j] * b[j];
        }

    }

}
