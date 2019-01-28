#pragma once

namespace ContrastChange {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Diagnostics;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для ExperimentForm
	/// </summary>
	public ref class ExperimentForm : public System::Windows::Forms::Form
	{
	public:
		ExperimentForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		void SetBind(ArrayList^  sets)
		{
			this->dataGridView1->DataSource = sets;
			this->dataGridView1->Refresh();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ExperimentForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	protected:





	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Size;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  SerialTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ParallelTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Accelerate;






















	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Size = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SerialTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ParallelTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Accelerate = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->Size, this->SerialTime,
					this->ParallelTime, this->Accelerate
			});
			this->dataGridView1->Location = System::Drawing::Point(37, 40);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(860, 396);
			this->dataGridView1->TabIndex = 0;
			// 
			// Size
			// 
			this->Size->DataPropertyName = L"Size";
			this->Size->HeaderText = L"Размер изображения";
			this->Size->Name = L"Size";
			this->Size->Width = 200;
			// 
			// SerialTime
			// 
			this->SerialTime->DataPropertyName = L"SerialTime";
			this->SerialTime->HeaderText = L"Последовательно";
			this->SerialTime->Name = L"SerialTime";
			// 
			// ParallelTime
			// 
			this->ParallelTime->DataPropertyName = L"ParallelTime";
			this->ParallelTime->HeaderText = L"Параллельно";
			this->ParallelTime->Name = L"ParallelTime";
			// 
			// Accelerate
			// 
			this->Accelerate->DataPropertyName = L"Acceleration";
			this->Accelerate->HeaderText = L"Ускорение";
			this->Accelerate->Name = L"Accelerate";
			// 
			// ExperimentForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(966, 518);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"ExperimentForm";
			this->Text = L"Экспериментальные данные";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
