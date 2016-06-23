#ifndef H_WORKER
#define H_WORKER

#pragma offload_attribute(push, target(mic))
void init_array(int* data, int size);
int CountNonZero(const int N, const int* arr);
#pragma offload_attribute(pop)

#endif
