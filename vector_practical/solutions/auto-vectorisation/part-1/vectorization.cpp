/* Copyright (c) 2013, Colfax International. All Right Reserved.
file vectorization.cpp, located at 3/3.1-vectorization/step-02
is a part of the practical supplement to the handbook
"Parallel Programming and Optimization with Intel Xeon Phi Coprocessors" 
(c) Colfax International, 2013, ISBN: 978-0-9885234-1-8
Redistribution or commercial usage without a written permission 
from Colfax International is prohibited.
Contact information can be found at http://colfax-intl.com/     */

#include <stdio.h>
#include <stdlib.h>

__declspec(noinline) void vadd(float* restrict A, float* restrict B, float* restrict C, int n)
{
    __assume_aligned(A,64);
    __assume_aligned(B,64);
    __assume_aligned(C,64);
    for (int i=0; i<n; ++i)
    {
        C[i] = A[i] + B[i];
    }
}

int main() {
  const int n=512;
  int i;
  float* A = (float*) _mm_malloc(n*sizeof(float),64);
  float* B = (float*) _mm_malloc(n*sizeof(float),64);
  float* C = (float*) _mm_malloc(n*sizeof(float),64);

  // Initialization
  for (i=0; i<n; i++)
    A[i]=B[i]= (float) i;

  vadd(A, B, C, n);

  // Output
  for (i=0; i<n; i++)
    printf("%f %f %f\n", A[i], B[i], C[i]);

  _mm_free(A);
  _mm_free(B);
  _mm_free(C);
}
