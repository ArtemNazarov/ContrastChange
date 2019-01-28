#pragma once

#ifdef _DLLEXPORT_
#define _DECLARATOR_ __declspec(dllexport)
#else
#define _DECLARATOR_ __declspec(dllimport)
#endif

extern "C"  
{
	 _DECLARATOR_ void* __cdecl equalizeHistogram(double* color, int Width, int Height);
	 _DECLARATOR_ void* __cdecl linearContrasting(int* color, int Width, int Height);
	 _DECLARATOR_ int __cdecl hhh(int check, double* arr);
}
