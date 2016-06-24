#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "mytime.h"

#define num_steps 1000000000

int main(int argc, char* argv[])
{
    int i;
	double start_time, stop_time;
	double x, step, sum = 0.0;
	double pi;

	printf("Hello, World from host. # procs = %d\n", omp_get_num_procs());
	printf("Calculating PI...\n");
				
	start_time = my_wtime();

	step = 1.0 / (double)num_steps;
#pragma offload target(mic) in(step, x), inout(sum), nocopy(i)
	#pragma omp parallel for private(x) reduction(+:sum)
	for (i=0; i<num_steps; i++)
	{
		x = (i + 0.5) * step;
		sum = sum + 4.0/(1.0 + x * x);
	}
	pi = sum * step;

	stop_time = my_wtime();

	printf("The value of PI is %.15f\n", pi);
	printf("The time to calculate PI was %lf seconds\n",stop_time - start_time);

	return 0;
}

