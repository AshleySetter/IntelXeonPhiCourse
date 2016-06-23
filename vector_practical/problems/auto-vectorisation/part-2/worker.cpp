/* Copyright (c) 2013, Colfax International. All Right Reserved.
file worker.cpp, located at 3/3.1-vectorization/step-0a
is a part of the practical supplement to the handbook
"Parallel Programming and Optimization with Intel Xeon Phi Coprocessors" 
(c) Colfax International, 2013, ISBN: 978-0-9885234-1-8
Redistribution or commercial usage without a written permission 
from Colfax International is prohibited.
Contact information can be found at http://colfax-intl.com/     */

void my_simple_add(int n, int* a, int* b){
  for (int i=0; i<n; i++)
      a[i] = b[i];
}