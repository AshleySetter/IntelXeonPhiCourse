/* Copyright (c) 2013, Colfax International. All Right Reserved.
file vectorization.cpp, located at 3/3.1-vectorization/step-04
is a part of the practical supplement to the handbook
"Parallel Programming and Optimization with Intel Xeon Phi Coprocessors" 
(c) Colfax International, 2013, ISBN: 978-0-9885234-1-8
Redistribution or commercial usage without a written permission 
from Colfax International is prohibited.
Contact information can be found at http://colfax-intl.com/     */

#include <stdio.h>
#include <stdlib.h>

int main(){
  const int n=8;
  const int al=64; //alignment
  int i;

  int *A = (int*) malloc(n*sizeof(*A));
  int *B = (int*) malloc(n*sizeof(*B));

  // Initialization
  for (i=0; i<n; i++)
    A[i]=B[i]=i;

  // This loop will be auto-vectorized
  A[0:n]+=B[0:n];

  // Output
  for (i=0; i<n; i++)
    printf("%2d %2d %2d\n", i, A[i], B[i]);

  free(A);
  free(B);
}
