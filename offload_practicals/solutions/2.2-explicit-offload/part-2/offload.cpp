/* Copyright (c) 2013, Colfax International. All Right Reserved.
file offload.cpp, located at 2/2.2-explicit-offload/step-04
is a part of the practical supplement to the handbook
"Parallel Programming and Optimization with Intel Xeon Phi Coprocessors" 
(c) Colfax International, 2013, ISBN: 978-0-9885234-1-8
Redistribution or commercial usage without a written permission 
from Colfax International is prohibited.
Contact information can be found at http://colfax-intl.com/     */

#include <stdio.h>
#include <stdlib.h>
#include "worker.h"

#pragma offload_attribute(push, target(mic))
const int size = 1000;
int data[size];

#pragma offload_attribute(pop)

int main( int argc, const char* argv[] ){

    #pragma offload target(mic)
	    init_array(&data[0], size);

    int numberOfNonZeroElements;
    #pragma offload target(mic)
        numberOfNonZeroElements = CountNonZero(size, data);

    printf("There are %d non-zero elements in the array.\n", numberOfNonZeroElements);
}
