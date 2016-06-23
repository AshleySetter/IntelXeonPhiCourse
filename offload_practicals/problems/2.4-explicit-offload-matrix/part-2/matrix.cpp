/* Copyright (c) 2013, Colfax International. All Right Reserved.
file matrix.cpp, located at 2/2.4-explicit-offload-matrix/step-02
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
    double b[n], c[m];
    double * A = (double*) malloc(sizeof(double)*n*m);

    // Cilk Plus array notation
    A[0:n*m]=1.0/(double)n;
    b[:]=1.0;
    c[:]=0;

    for ( int i = 0 ; i < m ; i++)
        for ( int j = 0 ; j < n ; j++)
            c[i] += A[i*n+j] * b[j];

    double norm = 0.0;
    for ( int i = 0 ; i < m ; i++)
        norm += (c[i] - 1.0)*(c[i] - 1.0);
    if (norm > 1e-10)
        printf("Norm is equal to %f\n", norm);
    else
        printf("Yep, we're good!\n");
}
