#include <iostream>

#include "MyString.h"

void string_study()
{
	MyString str = "abc";

	MyString str2(str);
	MyString str3 = "";
	str2 = str3;
	str3 = "aaa";

	std::cout << str3 << std::endl;

	str3[0] = 'b';

	std::cout << str3[0] << std::endl;

	MyString str4 = "";
	str4 = str2 + str3;
	std::cout << str4 << std::endl;
}

int main(int argc, char* argv[])
{
	string_study();
	return EXIT_SUCCESS;
}