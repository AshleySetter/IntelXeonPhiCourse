/* Copyright (c) 2013, Colfax International. All Right Reserved.
file offload.cpp, located at 2/2.2-explicit-offload/step-03
is a part of the practical supplement to the handbook
"Parallel Programming and Optimization with Intel Xeon Phi Coprocessors" 
(c) Colfax International, 2013, ISBN: 978-0-9885234-1-8
Redistribution or commercial usage without a written permission 
from Colfax International is prohibited.
Contact information can be found at http://colfax-intl.com/     */

#include <stdio.h>
#include <stdlib.h>

__attribute__((target(mic))) int CountNonZero(const int N, const int* arr){
    int nz=0;
    for ( int i = 0 ; i < N ; i++ ){
        if ( arr[i] != 0 ) nz++;
    }
    return nz;
}

int main( int argc, const char* argv[] ){

    int numberOfNonZeroElements; 

#pragma offload target(mic)
    {
        const int size = 1000;
        int data[size];

        // initialize array of integers
        for ( int i = 0; i < size ; i++) {
            data[i] = rand() % 10;
        }
    
        numberOfNonZeroElements = CountNonZero(size, data);
    }

    printf("There are %d non-zero elements in the array.\n", numberOfNonZeroElements);
}
