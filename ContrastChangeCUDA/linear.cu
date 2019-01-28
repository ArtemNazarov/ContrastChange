#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"
#include "linear.cuh"

__global__ void linearKernel(int* color, int width, int height)
{

}


void* linearContrast(int * color, int Width, int Height) {
	int* dev_col;
	int n = 32;
	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop, 0);
	cudaMalloc((void **)&dev_col, sizeof(int)*Height*Width * 5);
	cudaMemcpy(dev_col, color, sizeof(int)*Height*Width * 5, cudaMemcpyHostToDevice);
	dim3 grid((Width + prop.maxThreadsPerBlock / n - 1) / (prop.maxThreadsPerBlock / n), (Height + prop.maxThreadsPerBlock / n - 1) / (prop.maxThreadsPerBlock / n), 1);
	dim3 threads(prop.maxThreadsPerBlock / n, prop.maxThreadsPerBlock / n, 1);
	linearKernel << <grid, threads >> > (dev_col, Width, Height);
	cudaMemcpy(color, dev_col, sizeof(int)*Height*Width * 5, cudaMemcpyDeviceToHost);
	cudaFree(dev_col);
	return(color);
}