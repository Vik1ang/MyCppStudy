#include "MyString.h"

MyString::MyString(const char* str)
{
	this->pString = new char[strlen(str) + 1];
	strcpy(this->pString, str);
	this->m_Size = strlen(str);
}

MyString::MyString(const MyString& str)
{
	this->pString = new char[strlen(str.pString) + 1];
	strcpy(this->pString, str.pString);
	this->m_Size = m_Size;
}

MyString::~MyString()
{
	if (this->pString != nullptr)
	{
		delete[] this->pString;
		this->pString = nullptr;
	}
}

MyString& MyString::operator=(const char* str)
{
	if (this->pString != nullptr)
	{
		delete[] this->pString;
		this->pString = nullptr;
	}
	this->pString = new char[strlen(str) + 1];
	strcpy(this->pString, str);

	return *this;
}

MyString& MyString::operator=(const MyString& str)
{
	if (this->pString != nullptr)
	{
		delete[] this->pString;
		this->pString = nullptr;
	}
	this->pString = new char[strlen(str.pString) + 1];
	strcpy(this->pString, str.pString);

	return *this;
}

char& MyString::operator[](int index)
{
	return this->pString[index];
}

MyString MyString::operator+(const char* str)
{
	const int new_size = this->m_Size + strlen(str) + 1;
	char* tmp = new char[new_size];

	memset(tmp, 0, new_size);
	strcat(tmp, this->pString);
	strcat(tmp, str);

	MyString newStr(tmp);

	delete[] tmp;
	return newStr;
}

MyString MyString::operator+(const MyString& str)
{
	const int new_size = this->m_Size + strlen(str.pString) + 1;
	char* tmp = new char[new_size];

	memset(tmp, 0, new_size);
	strcat(tmp, this->pString);
	strcat(tmp, str.pString);

	MyString newStr(tmp);

	delete[] tmp;
	return newStr;
}

bool MyString::operator==(const char* str) const
{
	if (strcmp(this->pString, str) == 0 && this->m_Size == strlen(str))
	{
		return true;
	}
	return false;
}

bool MyString::operator==(const MyString& str) const
{
	if (strcmp(this->pString, str.pString) == 0 && this->m_Size == strlen(str.pString))
	{
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& cout, MyString& str)
{
	return cout << str.pString;
}

std::istream& operator>>(std::istream& cin, MyString& str)
{
	if (str.pString != nullptr)
	{
		delete[] str.pString;
		str.pString = nullptr;
	}
	char buf[1024];
	cin >> buf;
	str.pString = new char[strlen(buf) + 1];
	strcpy(str.pString, buf);
	str.m_Size = strlen(buf);

	return cin;
}