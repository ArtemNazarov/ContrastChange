#ifndef KERNEL
#define KERNEL

__global__ void equalizeKernel(int* color, int width, int height);
int equalizeHist(int * color, int width, int height);

#endif

