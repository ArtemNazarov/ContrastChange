#pragma once

namespace ContrastChange {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// —водка дл€ HistogramForm
	/// </summary>
	public ref class HistogramForm : public System::Windows::Forms::Form
	{
	public:
		HistogramForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

		void SetImage(Bitmap^ img)
		{
			this->MyImage = img;
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~HistogramForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(29, 22);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(762, 467);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			// 
			// HistogramForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(868, 518);
			this->Controls->Add(this->chart1);
			this->Name = L"HistogramForm";
			this->Text = L"√истограмма изображени€";
			this->Load += gcnew System::EventHandler(this, &HistogramForm::HistogramForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:  Bitmap^ MyImage;
	private: System::Void HistogramForm_Load(System::Object^  sender, System::EventArgs^  e) {
		this->chart1->Series->Clear();
		this->chart1->Titles->Add("√истограмма");
		Series^ redSeries = this->chart1->Series->Add("Red");
		redSeries->Color = Color::Red;
		Series^ greenSeries = this->chart1->Series->Add("Green");
		greenSeries->Color = Color::Green;
		Series^ blueSeries = this->chart1->Series->Add("Blue");
		blueSeries->Color = Color::Blue;
		redSeries->ChartType = SeriesChartType::Spline;
		greenSeries->ChartType = SeriesChartType::Spline;
		blueSeries->ChartType = SeriesChartType::Spline;

		array<int>^ red = gcnew array<int>(256);
		array<int>^ green = gcnew array<int>(256);
		array<int>^ blue = gcnew array<int>(256);
		int Width = MyImage->Width;
		int Height = MyImage->Height;

		for (int i = 0; i < Width; i++)
		{
			for (int j = 0; j < Height; j++)
			{
				if (!(i == 0 || j == 0 || i == Width - 1 || j == Height - 1)) {
					Color medium = MyImage->GetPixel(i - 1, j - 1);
					int R = medium.R;
					int G = medium.G;
					int B = medium.B;

					red[R] += 1;
					green[G] += 1;
					blue[B] += 1;
				}
			}
		}
		for (int i = 0; i < 256; i++)
		{
			redSeries->Points->AddXY(i,red[i]);
			greenSeries->Points->AddXY(i, green[i]);
			blueSeries->Points->AddXY(i, blue[i]);
		}

	}
	};

}
