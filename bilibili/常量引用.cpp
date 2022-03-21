#include <iostream>

void test01()
{
	//int& ref = 10; // 引用了不合法的内存, 不可以
	const int& ref = 10; //  加入const, 编译器处理方式: int tmp = 10; const int &ref = tmp;
	int* p = (int*)&ref;
	*p = 1000;

	std::cout << "ref = " << ref << std::endl;
}

void show_value(const int& val)
{
	std::cout << "val = " << val << std::endl;
}

void test02()
{
	int a = 10;
	show_value(a);
}