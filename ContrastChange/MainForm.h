#pragma once
#include "ImageContrast.h"
#include "ExperimentForm.h"
#include "HistogramForm.h"
#include "Accelerate.h"

struct img
{
	int width;
	int height;
	unsigned * image;
};


namespace ContrastChange {

	using namespace System;
	using namespace std;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections:: Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openFileStripMenu;

	private: System::Windows::Forms::ToolStripMenuItem^  сохранитьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  closeAppStripMenuItem;





	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^  дополнительноToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  experimentToolStrip;




	private: System::Windows::Forms::ToolStripMenuItem^  drawHistToolStripMenuItem;




	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TrackBar^  maxTrackBar;
	private: System::Windows::Forms::TrackBar^  minTrackBar;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  maxValueNumericBox;
	private: System::Windows::Forms::NumericUpDown^  minValueNumericBox;


	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  algCombo;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  contrastCombo;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  Status;
	private: System::Windows::Forms::Button^  btnChangeContrast;
	private: System::Windows::Forms::ProgressBar^  progressBar1;

	private: System::Windows::Forms::Label^  execLabel;











	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileStripMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeAppStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->дополнительноToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->experimentToolStrip = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawHistToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->maxTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->minTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->maxValueNumericBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->minValueNumericBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->contrastCombo = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->algCombo = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->execLabel = (gcnew System::Windows::Forms::Label());
			this->Status = (gcnew System::Windows::Forms::Label());
			this->btnChangeContrast = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->maxTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->minTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->maxValueNumericBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->minValueNumericBox))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Location = System::Drawing::Point(64, 187);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1320, 654);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Image files|*.jpg";
			this->openFileDialog1->RestoreDirectory = true;
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->файлToolStripMenuItem,
					this->дополнительноToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1457, 28);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openFileStripMenu,
					this->сохранитьToolStripMenuItem, this->closeAppStripMenuItem
			});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(57, 24);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// openFileStripMenu
			// 
			this->openFileStripMenu->Name = L"openFileStripMenu";
			this->openFileStripMenu->Size = System::Drawing::Size(162, 26);
			this->openFileStripMenu->Text = L"Открыть";
			this->openFileStripMenu->Click += gcnew System::EventHandler(this, &MainForm::openFileStripMenu_Click);
			// 
			// сохранитьToolStripMenuItem
			// 
			this->сохранитьToolStripMenuItem->Name = L"сохранитьToolStripMenuItem";
			this->сохранитьToolStripMenuItem->Size = System::Drawing::Size(162, 26);
			this->сохранитьToolStripMenuItem->Text = L"Сохранить ";
			this->сохранитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::сохранитьToolStripMenuItem_Click);
			// 
			// closeAppStripMenuItem
			// 
			this->closeAppStripMenuItem->Name = L"closeAppStripMenuItem";
			this->closeAppStripMenuItem->Size = System::Drawing::Size(162, 26);
			this->closeAppStripMenuItem->Text = L"Выход";
			this->closeAppStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::closeAppStripMenuItem_Click);
			// 
			// дополнительноToolStripMenuItem
			// 
			this->дополнительноToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->experimentToolStrip,
					this->drawHistToolStripMenuItem
			});
			this->дополнительноToolStripMenuItem->Name = L"дополнительноToolStripMenuItem";
			this->дополнительноToolStripMenuItem->Size = System::Drawing::Size(132, 24);
			this->дополнительноToolStripMenuItem->Text = L"Дополнительно";
			// 
			// experimentToolStrip
			// 
			this->experimentToolStrip->Name = L"experimentToolStrip";
			this->experimentToolStrip->Size = System::Drawing::Size(351, 26);
			this->experimentToolStrip->Text = L"Экспериментальные данные";
			this->experimentToolStrip->Click += gcnew System::EventHandler(this, &MainForm::experimentToolStrip_Click);
			// 
			// drawHistToolStripMenuItem
			// 
			this->drawHistToolStripMenuItem->Name = L"drawHistToolStripMenuItem";
			this->drawHistToolStripMenuItem->Size = System::Drawing::Size(351, 26);
			this->drawHistToolStripMenuItem->Text = L"Построить гистограмму изображения";
			this->drawHistToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::drawHistToolStripMenuItem_Click);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"Bmp image(*.bmp) | *.bmp | JPEG image (*.jpeg, *.jpg) | *.jpeg;*.jpg | All Files "
				L"(*.*)|*.*";
			this->saveFileDialog1->Title = L"Сохранить изображение";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->maxTrackBar);
			this->groupBox1->Controls->Add(this->minTrackBar);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->maxValueNumericBox);
			this->groupBox1->Controls->Add(this->minValueNumericBox);
			this->groupBox1->Location = System::Drawing::Point(64, 47);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(630, 133);
			this->groupBox1->TabIndex = 15;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Линейное контрастирование";
			// 
			// maxTrackBar
			// 
			this->maxTrackBar->Location = System::Drawing::Point(330, 65);
			this->maxTrackBar->Maximum = 255;
			this->maxTrackBar->Name = L"maxTrackBar";
			this->maxTrackBar->Size = System::Drawing::Size(294, 56);
			this->maxTrackBar->TabIndex = 18;
			this->maxTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::maxTrackBar_ValueChanged);
			// 
			// minTrackBar
			// 
			this->minTrackBar->Location = System::Drawing::Point(23, 62);
			this->minTrackBar->Maximum = 255;
			this->minTrackBar->Name = L"minTrackBar";
			this->minTrackBar->Size = System::Drawing::Size(271, 56);
			this->minTrackBar->TabIndex = 17;
			this->minTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::minTrackBar_ValueChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(327, 32);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(172, 17);
			this->label3->TabIndex = 16;
			this->label3->Text = L"Максимальное значение";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(20, 32);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(166, 17);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Минимальное значение";
			// 
			// maxValueNumericBox
			// 
			this->maxValueNumericBox->Location = System::Drawing::Point(506, 30);
			this->maxValueNumericBox->Margin = System::Windows::Forms::Padding(4);
			this->maxValueNumericBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
			this->maxValueNumericBox->Name = L"maxValueNumericBox";
			this->maxValueNumericBox->ReadOnly = true;
			this->maxValueNumericBox->Size = System::Drawing::Size(92, 22);
			this->maxValueNumericBox->TabIndex = 14;
			this->maxValueNumericBox->ValueChanged += gcnew System::EventHandler(this, &MainForm::maxValueNumericBox_ValueChanged);
			// 
			// minValueNumericBox
			// 
			this->minValueNumericBox->Location = System::Drawing::Point(202, 30);
			this->minValueNumericBox->Margin = System::Windows::Forms::Padding(4);
			this->minValueNumericBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
			this->minValueNumericBox->Name = L"minValueNumericBox";
			this->minValueNumericBox->ReadOnly = true;
			this->minValueNumericBox->Size = System::Drawing::Size(92, 22);
			this->minValueNumericBox->TabIndex = 13;
			this->minValueNumericBox->ValueChanged += gcnew System::EventHandler(this, &MainForm::minValueNumericBox_ValueChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->contrastCombo);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->algCombo);
			this->groupBox2->Location = System::Drawing::Point(716, 47);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(349, 133);
			this->groupBox2->TabIndex = 18;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Настройки алгоритма";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(2, 92);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(133, 17);
			this->label4->TabIndex = 20;
			this->label4->Text = L"Контрастирование";
			// 
			// contrastCombo
			// 
			this->contrastCombo->AllowDrop = true;
			this->contrastCombo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->contrastCombo->FormattingEnabled = true;
			this->contrastCombo->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Линейное контрастирование", L"Эквализация гистограммы" });
			this->contrastCombo->Location = System::Drawing::Point(141, 89);
			this->contrastCombo->Name = L"contrastCombo";
			this->contrastCombo->Size = System::Drawing::Size(202, 24);
			this->contrastCombo->TabIndex = 19;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(2, 35);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(129, 17);
			this->label1->TabIndex = 18;
			this->label1->Text = L"Версия алгоритма";
			// 
			// algCombo
			// 
			this->algCombo->AllowDrop = true;
			this->algCombo->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->algCombo->FormattingEnabled = true;
			this->algCombo->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Последовательный", L"Параллельный OpenMP", L"Параллельный CUDA" });
			this->algCombo->Location = System::Drawing::Point(141, 35);
			this->algCombo->Name = L"algCombo";
			this->algCombo->Size = System::Drawing::Size(202, 24);
			this->algCombo->TabIndex = 17;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->execLabel);
			this->groupBox3->Controls->Add(this->Status);
			this->groupBox3->Controls->Add(this->btnChangeContrast);
			this->groupBox3->Controls->Add(this->progressBar1);
			this->groupBox3->Location = System::Drawing::Point(1078, 47);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(365, 133);
			this->groupBox3->TabIndex = 19;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Выполнение";
			// 
			// execLabel
			// 
			this->execLabel->AutoSize = true;
			this->execLabel->Location = System::Drawing::Point(174, 65);
			this->execLabel->Name = L"execLabel";
			this->execLabel->Size = System::Drawing::Size(36, 17);
			this->execLabel->TabIndex = 22;
			this->execLabel->Text = L"0 мс";
			// 
			// Status
			// 
			this->Status->AutoSize = true;
			this->Status->Location = System::Drawing::Point(24, 65);
			this->Status->Name = L"Status";
			this->Status->Size = System::Drawing::Size(143, 17);
			this->Status->TabIndex = 20;
			this->Status->Text = L"Время выполнения: ";
			// 
			// btnChangeContrast
			// 
			this->btnChangeContrast->Location = System::Drawing::Point(25, 89);
			this->btnChangeContrast->Margin = System::Windows::Forms::Padding(4);
			this->btnChangeContrast->Name = L"btnChangeContrast";
			this->btnChangeContrast->Size = System::Drawing::Size(149, 28);
			this->btnChangeContrast->TabIndex = 18;
			this->btnChangeContrast->Text = L"Контрастирование";
			this->btnChangeContrast->UseVisualStyleBackColor = true;
			this->btnChangeContrast->Click += gcnew System::EventHandler(this, &MainForm::btnChangeContrast_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(24, 30);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(209, 28);
			this->progressBar1->TabIndex = 19;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1457, 965);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MainForm";
			this->Text = L"Контрастирование изображения";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->maxTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->minTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->maxValueNumericBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->minValueNumericBox))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:  Image^ MyImage;
			  String^ ImagePath;
			  ArrayList^  sets = gcnew ArrayList;
			  
	private: System::Void closeAppStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->Close();
	}
	private: System::Void openFileStripMenu_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			ShowMyImage(openFileDialog1->FileName, 400, 400);
		}
	}

	public:
		void ShowMyImage(String^ fileToDisplay, int xSize, int ySize)
		{

			// Sets up an image object to be displayed.
			if (MyImage != nullptr)
			{
				delete MyImage;
			}
			// Stretches the image to fit the pictureBox.
			pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
			//MyImage = gcnew Bitmap(fileToDisplay);
			//pictureBox1->ClientSize = System::Drawing::Size(MyImage->Width, MyImage->Height);

			MyImage = Bitmap::FromFile(fileToDisplay);
			ImagePath = fileToDisplay;
			pictureBox1->Image = MyImage;
		}



	private: System::Void btnChangeContrast_Click(System::Object^  sender, System::EventArgs^  e) {
		double elapsedTime = 0.0;
		if (this->pictureBox1->Image != nullptr) {

			if (contrastCombo->SelectedIndex == 0) {
				switch (algCombo->SelectedIndex) {
					case 0: 
						this->pictureBox1->Image = ImageContrast::AdjustContrast(gcnew Bitmap(MyImage), Convert::ToInt32(minValueNumericBox->Value), Convert::ToInt32(maxValueNumericBox->Value), progressBar1, &elapsedTime);
						break;
					case 1:
						this->pictureBox1->Image = ImageContrast::AdjustContrastOpenMP(gcnew Bitmap(MyImage), Convert::ToInt32(minValueNumericBox->Value), Convert::ToInt32(maxValueNumericBox->Value), progressBar1, &elapsedTime);
						break;
					case 2:
						this->pictureBox1->Image = ImageContrast::AdjustContrastCUDA(gcnew Bitmap(MyImage), Convert::ToInt32(minValueNumericBox->Value), Convert::ToInt32(maxValueNumericBox->Value), progressBar1, &elapsedTime);
						break;
				}
			}
			else {
				switch (algCombo->SelectedIndex) {
				case 0:
					this->pictureBox1->Image = ImageContrast::EqualizeHist(gcnew Bitmap(MyImage), progressBar1, &elapsedTime);
					break;
				case 1:
					this->pictureBox1->Image = ImageContrast::EqualizeHistOpenMP(gcnew Bitmap(MyImage), progressBar1, &elapsedTime);
					break;
				case 2:
					this->pictureBox1->Image = ImageContrast::EqualizeHistCUDA(gcnew Bitmap(MyImage), progressBar1, &elapsedTime);
					break;
				}
			}
			this->progressBar1->Value = 0;
			String^ size = MyImage->Width.ToString() + " X " + MyImage->Height.ToString();
			double serialTime = 0.0;
			double parallelTime = 9.0;
			double accelerateVal = 10.0;
			Accelerate^ accelerate = gcnew Accelerate(size, serialTime, parallelTime, accelerateVal);
			execLabel->Text = elapsedTime.ToString();
			//execLabel->Text = Convert::ToString(elapsedTime);
			sets->Add(accelerate);
		}
		else {
			String^ message = "Добавьте изображение!";
			String^ caption = "Ошибка!";
			MessageBoxButtons buttons = MessageBoxButtons::OK;
			MessageBox::Show(this, message, caption, buttons);
		}
	}

	private: System::Void сохранитьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			Bitmap^ bitmap = gcnew Bitmap(pictureBox1->Image);
			bitmap->Save(saveFileDialog1->FileName);
		}
	}
private: System::Void experimentToolStrip_Click(System::Object^  sender, System::EventArgs^  e) {
	ExperimentForm^ form = gcnew ExperimentForm();

	form->Show();
	form->SetBind(sets);
}
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	minValueNumericBox->Value = 0;
	maxValueNumericBox->Value = 255;
	algCombo->SelectedIndex = 0;
	contrastCombo->SelectedIndex = 0;
	String^ fileT = "C:\\Users\\artem\\Pictures\\overexposure.jpg";
	MyImage = Bitmap::FromFile(fileT);
	ImagePath = fileT;
	pictureBox1->Image = MyImage;
}
private: System::Void drawHistToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	HistogramForm^ form = gcnew HistogramForm();
	form->SetImage(gcnew Bitmap(this->pictureBox1->Image));
	form->Show();
}
private: System::Void maxTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	maxValueNumericBox->Value = maxTrackBar->Value;
}
private: System::Void minTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	if (minTrackBar->Value > maxTrackBar->Value) {
		String^ message = "Минимальное пороговое значение должно быть меньше максимального!";
		String^ caption = "Ошибка!";
		MessageBoxButtons buttons = MessageBoxButtons::OK;
		MessageBox::Show(this, message, caption, buttons);
		minTrackBar->Value = maxTrackBar->Value;
	}
	else {
		minValueNumericBox->Value = minTrackBar->Value;
	}
}
private: System::Void minValueNumericBox_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	if (minValueNumericBox->Value > maxValueNumericBox->Value) {
		String^ message = "Минимальное пороговое значение должно быть меньше максимального!";
		String^ caption = "Ошибка!";
		MessageBoxButtons buttons = MessageBoxButtons::OK;
		MessageBox::Show(this, message, caption, buttons);
		minValueNumericBox->Value = maxValueNumericBox->Value;
	}
	else {
		minTrackBar->Value = Convert::ToInt32(minValueNumericBox->Value);

	}
}
private: System::Void maxValueNumericBox_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	maxTrackBar->Value = Convert::ToInt32(maxValueNumericBox->Value);
}
};
}
