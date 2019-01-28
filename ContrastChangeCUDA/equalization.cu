#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"
#include "equalization.cuh"

#define H_SIZE 256


//__global__ void frKernel(double* color)
//{
//
//}

__global__ void equalizeKernel(double* color, int width, int height) {
	int idx = blockIdx.x*blockDim.x + threadIdx.x;
	int jdy = blockIdx.y*blockDim.y + threadIdx.y;

	if (idx == 0 || jdy == 0 || idx == width - 1 || jdy == height - 1)
		color[idx*width + jdy] = color[idx*width + jdy];
	else {
		int col = 0;
		color[idx * width + jdy] /= width * height;
		color[idx * width + jdy] /= color[idx * width + jdy] + color[(idx - 1) * width + jdy];
	}
}

void* equalizeHist(double * color, int Width, int Height) {
	double* dev_color;
	int n = 32;
	cudaDeviceProp prop;
	size_t size = sizeof(double) * Width * Height;
	cudaGetDeviceProperties(&prop, 0);
	cudaError_t result = cudaMalloc((void **)&dev_color, size);
	if (result != cudaError::cudaSuccess) {
		return NULL;
	}
	result = cudaMemcpy(dev_color, color, size, cudaMemcpyHostToDevice);
	if (result != cudaError::cudaSuccess) {
		return NULL;
	}
	dim3 grid((Width + prop.maxThreadsPerBlock / n - 1) / (prop.maxThreadsPerBlock / n), (Height + prop.maxThreadsPerBlock / n - 1) / (prop.maxThreadsPerBlock / n), 1);
	dim3 threads(prop.maxThreadsPerBlock / n, prop.maxThreadsPerBlock / n, 1);
	//dim3 threads(128, 128);
	//dim3 blocks((Width + threads.x - 1) / threads.x, (Height + threads.y - 1) / threads.y);
	equalizeKernel << <grid, threads >> > (dev_color, Width, Height);
	cudaMemcpy(color, dev_color, size, cudaMemcpyDeviceToHost);
	cudaFree(dev_color);
	return(color);
}

void calclc(int* erg) {

}

int calculate(double* erg) {
	double * dev_srcImage;
	size_t size = sizeof(double) * 2 * 4;

	if (cudaMalloc((void**)&dev_srcImage, size) != cudaError::cudaSuccess) return -1;
	// Максимальное количество нитей на блок может отличаться
	dim3 threads(128, 128);
	dim3 blocks((threads.x - 1) / threads.x, (threads.y - 1) /
		threads.y);
	//kernel << <threads, blocks >> > (dev_srcImage, width, height);
	cudaError error = cudaMemcpy(erg, dev_srcImage, size,
		cudaMemcpyDeviceToHost);
	if (error != cudaError::cudaSuccess) return -1;
	cudaFree(dev_srcImage);
	return 0;
}