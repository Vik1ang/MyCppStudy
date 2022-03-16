#pragma once

#include <cstring>
#include <iostream>

class MyString
{
	friend std::ostream& operator<<(std::ostream& cout, MyString& str);
	friend std::istream& operator>>(std::istream& cin, MyString& str);
public:
	MyString(const char* str);
	MyString(const MyString& str);

	~MyString();

	MyString& operator=(const char* str);
	MyString& operator=(const MyString& str);

	char& operator[](int index);

	MyString operator+(const char* str);
	MyString operator+(const MyString& str);

	bool operator==(const char* str) const;
	bool operator==(const MyString& str) const;
private:
	char* pString;
	int m_Size;
};
