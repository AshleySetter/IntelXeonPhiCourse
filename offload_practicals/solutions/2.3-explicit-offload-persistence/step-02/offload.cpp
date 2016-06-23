/* Copyright (c) 2013, Colfax International. All Right Reserved.
file offload.cpp, located at 2/2.3-explicit-offload-persistence/step-02
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

    double sumHost = 0;
    const long N=10000;
    double *p = (double*) malloc(N*sizeof(double));
    p[0:N] = 1.0; // Cilk Plus array notation

#pragma offload target (mic:0) in(p : length(N)) inout(sum:free_if(0))
    {
        for ( long i = 0 ; i < N ; i++ ) {
            sum += p[i];
        }
    }

    printf("After the offload: sum = %f \n", sum);
    sum += 1.0;
    printf("Data change on the host: sum = %f \n", sum);

#pragma offload_transfer target (mic:0) out(sum:alloc_if(0) free_if(1))

    printf("Copy data back from coprocessor: sum = %f \n", sum);
}
