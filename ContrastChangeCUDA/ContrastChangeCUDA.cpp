#include <windows.h>
#include "ContrastChangeCUDA.h"
#include "equalization.cuh"
#include "linear.cuh"


void* equalizeHistogram(double* color, int Width, int Height) {
	return equalizeHist(color, Width, Height);
}


void* linearContrasting(int* color, int Width, int Height){
	return linearContrast(color, Width, Height);
}

int hhh(int check, double* arr) {
	return 123 + check + calculate(arr);
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}