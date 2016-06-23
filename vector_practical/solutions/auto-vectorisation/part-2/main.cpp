/* Copyright (c) 2013, Colfax International. All Right Reserved.
file main.cpp, located at 3/3.1-vectorization/step-0a
is a part of the practical supplement to the handbook
"Parallel Programming and Optimization with Intel Xeon Phi Coprocessors" 
(c) Colfax International, 2013, ISBN: 978-0-9885234-1-8
Redistribution or commercial usage without a written permission 
from Colfax International is prohibited.
Contact information can be found at http://colfax-intl.com/     */

#include <stdio.h>

void my_simple_add(int, int*, int*);

int main(){
  const int n=16;
  int i;
  int A[n];
  int B[n];

  // Initialization
  for (i=0; i<n; i++)
    A[i]=B[i]=i;

  // This loop will be auto-vectorized
  my_simple_add(n-1, B+1, B);

  // Output
  for (i=0; i<n; i++)
    printf("%2d %2d %2d\n", i, A[i], B[i]);
}
