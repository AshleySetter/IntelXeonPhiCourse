/* Copyright (c) 2013, Colfax International. All Right Reserved.
file offload.cpp, located at 2/2.3-explicit-offload-persistence/step-01
is a part of the practical supplement to the handbook
"Parallel Programming and Optimization with Intel Xeon Phi Coprocessors" 
(c) Colfax International, 2013, ISBN: 978-0-9885234-1-8
Redistribution or commercial usage without a written permission 
from Colfax International is prohibited.
Contact information can be found at http://colfax-intl.com/     */

#include <stdio.h>
#include <stdlib.h>

__attribute__((target(mic))) double sum = 0;

int main(){

    const long N=10000;
    double *p = (double*) malloc(N*sizeof(double));
    p[0:N] = 1.0; // Cilk Plus array notation

#pragma offload target (mic) in(p : length(N)) inout(sum)
    {
        for ( long i = 0 ; i < N ; i++ ) {
            sum += p[i];
        }
    }
    printf("\nsum = %f\n", sum);
}
