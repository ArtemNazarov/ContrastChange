using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Windows::Forms;


	class ImageContrast
	{
	public:
		static Bitmap^ AdjustContrast(Bitmap^ , int , int , ProgressBar^, double*);
		static Bitmap^ AdjustContrastOpenMP(Bitmap^, int, int, ProgressBar^, double*);
		static Bitmap^ AdjustContrastCUDA(Bitmap^, int, int, ProgressBar^, double*);
		static Bitmap^ EqualizeHist(Bitmap^ Image, ProgressBar^ Bar, double*);
		static Bitmap^ EqualizeHistOpenMP(Bitmap^ Image, ProgressBar^ Bar, double*);
		static Bitmap^ EqualizeHistCUDA(Bitmap^ Image, ProgressBar^ Bar, double*);

	};

