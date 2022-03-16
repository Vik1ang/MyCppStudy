#include "MyArray.h"

MyArray::MyArray()
{
	this->m_Capacity = 100;
	this->m_Size = 0;
	this->pAddress = new int[this->m_Capacity];
}

MyArray::MyArray(int capacity)
{
	this->m_Capacity = capacity;
	this->m_Size = 0;
	this->pAddress = new int[this->m_Capacity];
}

MyArray::MyArray(const MyArray& array)
{
	this->m_Capacity = array.m_Capacity;
	this->m_Size = array.m_Size;
	this->pAddress = new int[array.m_Capacity];

	for (int i = 0; i < array.m_Size; ++i)
	{
		this->pAddress[i] = array.pAddress[i];
	}
}

MyArray::~MyArray()
{
	if (this->pAddress != nullptr)
	{
		delete[] this->pAddress;
		this->pAddress = nullptr;
	}
}

void MyArray::push_back(const int val)
{
	this->pAddress[this->m_Size] = val;
	this->m_Size++;
}

int MyArray::get_value(const int index) const
{
	return this->pAddress[index];
}

void MyArray::set_value(const int index, const int value)
{
	this->pAddress[index] = value;
}

int MyArray::get_size() const
{
	return this->m_Size;
}

int MyArray::get_capacity() const
{
	return this->m_Capacity;
}

int& MyArray::operator[](int index) const
{
	return this->pAddress[index];
}