#pragma once
using namespace System;
 ref class Accelerate
{
public:
	Accelerate();


private:

	String^ _size;

	double _serialTime;

	double _parallelTime;

	double _accelerate;

public:

	Accelerate(String^ Size, double SerialTime, double ParallelTime, double Accelerate)

	{

		this->_size = Size;

		this->_serialTime = SerialTime;

		this->_parallelTime = ParallelTime;

		this->_accelerate = Accelerate;

	}

	[System::ComponentModel::Bindable(true)]

	property String^ Size

	{

		String^   get() { return _size; }

		void set(String^ value) { _size = value; }

	}
	[System::ComponentModel::Bindable(true)]
	property double SerialTime

	{

		double   get() { return _serialTime; }

		void set(double value) { _serialTime = value; }

	}
	[System::ComponentModel::Bindable(true)]
	property double ParallelTime

	{

		double   get() { return _parallelTime; }

		void set(double value) { _parallelTime = value; }

	}
	[System::ComponentModel::Bindable(true)]
	property double Acceleration

	{

		double   get() { return _accelerate; }

		void set(double value) { _accelerate = value; }

	}

};

