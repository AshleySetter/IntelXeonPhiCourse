#include <stdio.h>
#include <stdlib.h>
#include "worker.h"

void init_array(int* data, int size)
{
    // initialize array of integers
    for ( int i = 0; i < size ; i++) {
        data[i] = rand() % 10;
    }
}

int CountNonZero(const int N, const int* arr){
    int nz=0;
    for ( int i = 0 ; i < N ; i++ ){
        if ( arr[i] != 0 ) nz++;
    }
    return nz;
}

