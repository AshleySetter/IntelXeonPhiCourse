/* Copyright (c) 2013, Colfax International. All Right Reserved.
file main.cpp, located at 3/3.1-vectorization/step-09
is a part of the practical supplement to the handbook
"Parallel Programming and Optimization with Intel Xeon Phi Coprocessors" 
(c) Colfax International, 2013, ISBN: 978-0-9885234-1-8
Redistribution or commercial usage without a written permission 
from Colfax International is prohibited.
Contact information can be found at http://colfax-intl.com/     */

#include <stdio.h>

#pragma declare simd
int my_simple_add(int, int);

int main(){
  const int n=512;
  const int al=64; //alignment
  int i;
  int* A = (int*) _mm_malloc(n*sizeof(int), al);
  int* B = (int*) _mm_malloc(n*sizeof(int), al);

  // Initialization
  for (i=0; i<n; i++)
    A[i]=B[i]=i;

  // This loop will be auto-vectorized
#pragma omp simd
  for (i=0; i<n; i++)
    A[i] = my_simple_add(A[i], B[i]);

  // Output
  for (i=0; i<n; i++)
    printf("%2d %2d %2d\n", i, A[i], B[i]);

  _mm_free(A);
  _mm_free(B);
}
