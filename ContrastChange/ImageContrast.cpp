#pragma once
#include <omp.h>
#include <Windows.h>
#include "ImageContrast.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Windows::Forms;

//ColorMatrix ^ ImageContrast::ChangeContrast(Bitmap ^ img, float contrast)
//{
//	Bitmap^ nImage = gcnew Bitmap(img->Width, img->Height);
//	float t = (1.0 - contrast) / 2.0;
//	//for (int i = 0; i < img->Width; i++)
//	//	for (int j = 0; j < img->Height; j++)
//	//	{
//	//		if (i == 0 || j == 0 || i == img->Width - 1 || j == img->Height - 1)
//	//			nImage->SetPixel(i, j, img->GetPixel(i, j));
//	//		else
//	//		{
//	//			int R = 0;
//	//			int G = 0;
//	//			int B = 0;
//	//			for (int k = 0; k < 3; k++)
//	//				for (int p = 0; p < 3; p++)
//	//				{
//	//					Color medium = image->GetPixel(i - 1 + k, j - 1 + p);
//	//					R += medium.R*GaussKernel[k][p];
//	//					G += medium.G*GaussKernel[k][p];
//	//					B += medium.B*GaussKernel[k][p];
//	//				}
//	//			nImage->SetPixel(i, j, Color::FromArgb(R / 16, G / 16, B / 16));
//	//		}
//	//	}
//
//	
//	array<array<float>^>^ contrastMatrix =
//	{
//		{
//			contrast,
//			0,
//			0,
//			0,
//			0
//		},
//		{
//			0,
//			contrast,
//			0,
//			0,
//			0,
//		},
//		{
//			0,
//			0,
//			contrast,
//			0,
//			0
//		},
//		{
//			0,
//			0,
//			0,
//			1,
//			0
//		},
//		{
//			t,
//			t,
//			t,
//			0,
//			1
//		},
//	};
//
//	float gamma = 1.0f;
//	Graphics^ g = Graphics::FromImage(img);
//	ImageAttributes^ imageAttributes = gcnew ImageAttributes();
//	imageAttributes->ClearColorMatrix();
//	imageAttributes->SetColorMatrix(gcnew ColorMatrix(contrastMatrix), ColorMatrixFlag::Default, ColorAdjustType::Bitmap);
//	imageAttributes->SetGamma(gamma, ColorAdjustType::Bitmap);
//	//ColorMatrix^ colorMatrix = gcnew ColorMatrix(contrastMatrix);
//	g->DrawImage(img, gcnew Rectangle(0, 0, nImage->Width, nImage->Height)
//		, 0, 0, img->Width, img->Height,
//		GraphicsUnit::Pixel, imageAttributes);
//
//	return nImage;
//}

Bitmap^ ImageContrast::AdjustContrast(Bitmap^ Image, int minValue, int maxValue, ProgressBar^ Bar, double* elapsedTime)
{

	float contrast = maxValue - minValue;
	Bitmap^ NewBitmap = (Bitmap^)Image->Clone();
	int Height = NewBitmap->Height;
	int Width = NewBitmap->Width;
	double maxBrightness = 0;
	double minBrightness = 100;
	double startTime = omp_get_wtime();

	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Height; j++)
		{
			if (!(i == 0 || j == 0 || i == Width - 1 || j == Height - 1)) {
				double brightness = Image->GetPixel(i, j).GetBrightness();
				if (maxBrightness < brightness)
					maxBrightness = brightness;
				if (minBrightness > brightness)
					minBrightness = brightness;
			}
		}
	}

	Bar->Minimum = 0;
	Bar->Value = 0;
	Bar->Maximum = Image->Width*Image->Height;																																																																												

	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Height; j++)
		{
			if (i == 0 || j == 0 || i == Width - 1 || j == Height - 1)
				NewBitmap->SetPixel(i, j, Image->GetPixel(i, j));
			else
			{
				int R = 0;
				int G = 0;
				int B = 0;
				Color medium = Image->GetPixel(i - 1, j - 1);
				double brightness = medium.GetBrightness();
				double Red = medium.R / 255.0f;
				double Green = medium.G / 255.0f;
				double Blue = medium.B / 255.0f;
				double maxVal = maxValue / 255.0f;
				double minVal = minValue / 255.0f;
				double a = (maxVal - minVal) / (maxBrightness - minBrightness);
				double b = (minVal * maxBrightness - maxVal * minBrightness) / (maxBrightness - minBrightness);
				Red = (a * Red + b) * 255.0f;
				Green = (a * Green + b) * 255.0f;
				Blue = (a * Blue  + b) * 255.0f;

				int iR = (int)Red;
				iR = iR > 255 ? 255 : iR;
				iR = iR < 0 ? 0 : iR;
				int iG = (int)Green;
				iG = iG > 255 ? 255 : iG;
				iG = iG < 0 ? 0 : iG;
				int iB = (int)Blue;
				iB = iB > 255 ? 255 : iB;
				iB = iB < 0 ? 0 : iB;

				NewBitmap->SetPixel(i, j, Color::FromArgb(iR, iG, iB));
				Bar->Value++;
			}
		}
	*elapsedTime = omp_get_wtime() - startTime;


	return NewBitmap;

}

Bitmap^ ImageContrast::AdjustContrastOpenMP(Bitmap^ Image, int minValue, int maxValue, ProgressBar^ Bar, double* elapsedTime)
{

	double contrast = maxValue - minValue;
	//contrast = (100.0f + contrast) / 100.0f;
	Bitmap^ NewBitmap = (Bitmap^)Image->Clone();
	int Height = NewBitmap->Height;
	int Width = NewBitmap->Width;
	double maxBrightness = 0;
	double minBrightness = 100;

	omp_set_dynamic(1);
	if (omp_get_dynamic() == 0)
		omp_set_num_threads(omp_get_max_threads());


	double startTime = omp_get_wtime();
#pragma omp for 
	for (int i = 0; i < Width; i++)
	for (int j = 0; j < Height; j++)
	{
		if (!(i == 0 || j == 0 || i == Width - 1 || j == Height - 1)) {
			double brightness = Image->GetPixel(i, j).GetBrightness();
			if (maxBrightness < brightness)
				maxBrightness = brightness;
			if (minBrightness > brightness)
				minBrightness = brightness;
		}
	}


	Bar->Minimum = 0;
	Bar->Value = 0;
	Bar->Maximum = Image->Width*Image->Height;

#pragma omp for 
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Height; j++)
		{
			if (i == 0 || j == 0 || i == Width - 1 || j == Height - 1)
				NewBitmap->SetPixel(i, j, Image->GetPixel(i, j));
			else
			{
				int R = 0;
				int G = 0;
				int B = 0;
				Color medium = Image->GetPixel(i - 1, j - 1);
				double brightness = medium.GetBrightness();
				double Red = medium.R / 255.0f;
				double Green = medium.G / 255.0f;
				double Blue = medium.B / 255.0f;
				//Red = (((Red - 0.5f) * contrast) + 0.5f) * 255.0f;
				//Green = (((Green - 0.5f) * contrast) + 0.5f) * 255.0f;
				//Blue = (((Blue - 0.5f) * contrast) + 0.5f) * 255.0f;
				double maxVal = maxValue / 255.0f;
				double minVal = minValue / 255.0f;
				double a = (maxVal - minVal) / (maxBrightness - minBrightness);
				double b = (minVal * maxBrightness - maxVal * minBrightness) / (maxBrightness - minBrightness);
				Red = (a * Red + b) * 255.0f;
				Green = (a * Green + b) * 255.0f;
				Blue = (a * Blue + b) * 255.0f;

				int iR = (int)Red;
				iR = iR > 255 ? 255 : iR;
				iR = iR < 0 ? 0 : iR;
				int iG = (int)Green;
				iG = iG > 255 ? 255 : iG;
				iG = iG < 0 ? 0 : iG;
				int iB = (int)Blue;
				iB = iB > 255 ? 255 : iB;
				iB = iB < 0 ? 0 : iB;

				NewBitmap->SetPixel(i, j, Color::FromArgb(iR, iG, iB));
				Bar->Value++;
			}
		}
	*elapsedTime = omp_get_wtime() - startTime;


	return NewBitmap;

}

Bitmap^ ImageContrast::AdjustContrastCUDA(Bitmap^ Image, int minValue, int maxValue, ProgressBar^ Bar, double* elapsedTime)
{

	double contrast = maxValue - minValue;


	double startTime = omp_get_wtime();

	//contrast = (100.0f + contrast) / 100.0f;
	Bitmap^ NewBitmap = (Bitmap^)Image->Clone();
	*elapsedTime = omp_get_wtime() - startTime;

	return NewBitmap;
} 

Bitmap^ ImageContrast::EqualizeHist(Bitmap^ Image, ProgressBar^ Bar, double* elapsedTime)
{
	int size = 256;
	array<double>^ red = gcnew array<double>(size);
	array<double>^ green = gcnew array<double>(size);
	array<double>^ blue = gcnew array<double>(size);

	Bitmap^ NewBitmap = (Bitmap^)Image->Clone();
	int Height = NewBitmap->Height;
	int Width = NewBitmap->Width;
	Bar->Minimum = 0;
	Bar->Value = 0;
	Bar->Maximum = Image->Width*Image->Height;

	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Height; j++)
		{
			if (!(i == 0 || j == 0 || i == Width - 1 || j == Height - 1)) {
				Color medium = Image->GetPixel(i - 1, j - 1);
				int R = medium.R;
				red[R] += 1;
				int G = medium.G;
				green[G] += 1;
				int B = medium.B;
				blue[B] += 1;
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		red[i] /= (Width * Height);
		green[i] /= (Width * Height);
		blue[i] /= (Width * Height);
	}
	for (int i = 1; i < size; i++)
	{
		red[i] = red[i - 1] + red[i];
		green[i] = green[i - 1] + green[i];
		blue[i] = blue[i - 1] + blue[i];
	}

	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Height; j++)
		{
			if (!(i == 0 || j == 0 || i == Width - 1 || j == Height - 1)) {
				Color medium = Image->GetPixel(i - 1, j - 1);
				int indexR = medium.R;
				int indexG = medium.G;
				int indexB = medium.B;

				NewBitmap->SetPixel(i, j, Color::FromArgb(red[indexR] * size, green[indexG] * size, blue[indexB] * size));
			}
			else {
				Color medium = Image->GetPixel(i, j);
				int indexR = medium.R;
				int indexG = medium.G;
				int indexB = medium.B;
				NewBitmap->SetPixel(i, j, Color::FromArgb(indexR, indexG, indexB));
			}
		}
	}
	return NewBitmap;

}

Bitmap^ ImageContrast::EqualizeHistOpenMP(Bitmap^ Image, ProgressBar^ Bar, double* elapsedTime)
{
	int size = 256;
	array<double>^ red = gcnew array<double>(size);
	array<double>^ green = gcnew array<double>(size);
	array<double>^ blue = gcnew array<double>(size);

	Bitmap^ NewBitmap = (Bitmap^)Image->Clone();
	int Height = NewBitmap->Height;
	int Width = NewBitmap->Width;
	Bar->Minimum = 0;
	Bar->Value = 0;
	Bar->Maximum = Image->Width*Image->Height;

#pragma omp for schedule(guided)
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Height; j++)
		{
			if (!(i == 0 || j == 0 || i == Width - 1 || j == Height - 1)) {
				Color medium = Image->GetPixel(i - 1, j - 1);
				int R = medium.R;
				red[R] += 1;
				int G = medium.G;
				green[G] += 1;
				int B = medium.B;
				blue[B] += 1;
			}
		}
#pragma omp for schedule(guided)
	for (int i = 0; i < size; i++)
	{
		red[i] /= (Width * Height);
		green[i] /= (Width * Height);
		blue[i] /= (Width * Height);
	}
#pragma omp for schedule(guided)
	for (int i = 1; i < size; i++)
	{
		red[i] = red[i - 1] + red[i];
		green[i] = green[i - 1] + green[i];
		blue[i] = blue[i - 1] + blue[i];
	}
#pragma omp for schedule(guided)
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Height; j++)
		{
			if (!(i == 0 || j == 0 || i == Width - 1 || j == Height - 1)) {
				Color medium = Image->GetPixel(i - 1, j - 1);
				int indexR = medium.R;
				int indexG = medium.G;
				int indexB = medium.B;

				NewBitmap->SetPixel(i, j, Color::FromArgb(red[indexR] * size, green[indexG] * size, blue[indexB] * size));
			}
			else {
				Color medium = Image->GetPixel(i, j);
				int indexR = medium.R;
				int indexG = medium.G;
				int indexB = medium.B;
				NewBitmap->SetPixel(i, j, Color::FromArgb(indexR, indexG, indexB));
			}
		}
	return NewBitmap;

}

Bitmap^ ImageContrast::EqualizeHistCUDA(Bitmap^ Image, ProgressBar^ Bar, double* elapsedTime)
{
	Bitmap^ NewBitmap = (Bitmap^)Image->Clone();
	
	Bar->Minimum = 0;
	Bar->Value = 0;
	Bar->Maximum = Image->Width*Image->Height;
	double startTime = omp_get_wtime();
	double* R = new double[Image->Width*Image->Height * 2];
	double* G = new double[Image->Width*Image->Height * 2];
	double* B = new double[Image->Width*Image->Height * 2];
	for (int i = 0; i < Image->Width; i++)
		for (int j = 0; j < Image->Height; j++)
		{
			R[i*Image->Width + j] = Image->GetPixel(i, j).R;
			G[i*Image->Width + j] = Image->GetPixel(i, j).G;
			B[i*Image->Width + j] = Image->GetPixel(i, j).B;
			if (j % 4 == 0) Bar->Value++;
		}
	HINSTANCE hGetProcIDDLL = LoadLibrary(L"ContrastChangeCUDA.dll");
	if (!hGetProcIDDLL)
	{
		throw gcnew Exception();
	}

	typedef int(__stdcall * function)(void *, int, int);
	function equalizeHist = (function)GetProcAddress(hGetProcIDDLL, "equalizeHistogram");

	if (!equalizeHist)
	{
		throw gcnew Exception();
	}

	function cal = (function)GetProcAddress(hGetProcIDDLL, "hhh");

	Bar->Value = Bar->Maximum / 4;
	R = (double*)equalizeHist(R, Image->Width, Image->Height);
	Bar->Value += Bar->Maximum / 4;
	G = (double*)equalizeHist(G,  Image->Width, Image->Height);
	Bar->Value += Bar->Maximum / 4;
	B = (double*)equalizeHist(B, Image->Width, Image->Height);
	Bar->Value += Bar->Maximum / 4;
	for (int i = 0; i < Image->Width; i++)
		for (int j = 0; j < Image->Height; j++)
			NewBitmap->SetPixel(i, j, Color::FromArgb(R[i*Image->Width + j], G[i*Image->Width + j], B[i*Image->Width + j]));

	*elapsedTime = omp_get_wtime() - startTime;


	return NewBitmap;
}

//Bitmap^ ImageContrast::AdjustContrast(Bitmap^ Image, float contrast)
//{
//
//	contrast = (100.0f + contrast) / 100.0f;
//	//contrast *= contrast;
//	Bitmap^ NewBitmap = (Bitmap^)Image->Clone();
//	int Height = NewBitmap->Height;
//	int Width = NewBitmap->Width;
//	float maxBrightness = 0;
//	float minBrightness = 100;
//	for (int i = 0; i < Width; i++)
//	{
//		for (int j = 0; j < Height; j++)
//		{
//			float brightness = Image->GetPixel(i, j).GetBrightness() * 100;
//			if (maxBrightness < brightness)
//				maxBrightness = brightness;
//			if (minBrightness > brightness)
//				minBrightness = brightness;
//		}
//	}
//
//
//
//	for (int i = 0; i < Width; i++)
//		for (int j = 0; j < Height; j++)
//		{
//			//Image->GetPixel(i, j).gET
//			if (i == 0 || j == 0 || i == Width - 1 || j == Height - 1)
//				NewBitmap->SetPixel(i, j, Image->GetPixel(i, j));
//			else
//			{
//				int R = 0;
//				int G = 0;
//				int B = 0;
//				Color medium = Image->GetPixel(i - 1, j - 1);
//				float brightness = medium.GetBrightness();
//				float Red = medium.R / 255.0f;
//				float Green = medium.G / 255.0f;
//				float Blue = medium.B / 255.0f;
//				Red = (((Red - 0.5f) * contrast) + 0.5f) * 255.0f;
//				Green = (((Green - 0.5f) * contrast) + 0.5f) * 255.0f;
//				Blue = (((Blue - 0.5f) * contrast) + 0.5f) * 255.0f;
//
//				int iR = (int)Red;
//				iR = iR > 255 ? 255 : iR;
//				iR = iR < 0 ? 0 : iR;
//				int iG = (int)Green;
//				iG = iG > 255 ? 255 : iG;
//				iG = iG < 0 ? 0 : iG;
//				int iB = (int)Blue;
//				iB = iB > 255 ? 255 : iB;
//				iB = iB < 0 ? 0 : iB;
//
//				NewBitmap->SetPixel(i, j, Color::FromArgb(iR, iG, iB));
//			}
//		}
//	//*elapsedTime = omp_get_wtime() - statrtime;
//
//
//	return NewBitmap;
//
//}




