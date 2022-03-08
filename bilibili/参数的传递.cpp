#include <iostream>
#include <ostream>
// 指针传递
void mySwap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void test01()
{
	int a = 10;
	int b = 20;
	mySwap(&a, &b);

	std::cout << "a = " << std::endl;
	std::cout << "b = " << std::endl;
}

// 引用传递
void mySwap02(int& a, int& b) // &a = a, &b = b
{
	int temp = a;
	a = b;
	b = temp;
}

void test02()
{
	int a = 10;
	int b = 20;
	mySwap02(a, b);

	std::cout << "a = " << std::endl;
	std::cout << "b = " << std::endl;
}

// 注意事项
// 1. 引用必须引一块合法的内存空间
// 2. 不要返回局部变量的引用

// 不要返回局部变量的引用
int& doWork()
{
	int a = 10;
	return a;
}

int& doWork2()
{
	static int a = 10;
	return a;
}

void test03()
{
	// int &a = 10; // 引用必须引一块合法的内存空间
	int& ret = doWork(); // 不要返回局部变量的引用
	std::cout << "ret = " << ret << std::endl; // 10 其实是编译器做了优化
	std::cout << "ret = " << ret << std::endl; // 未知
	std::cout << "ret = " << ret << std::endl; // 未知
	std::cout << "ret = " << ret << std::endl; // 未知

	int& ret2 = doWork2();
	std::cout << "ret2 = " << ret2 << std::endl; // 10 其实是编译器做了优化
	std::cout << "ret2 = " << ret2 << std::endl; // 未知
	std::cout << "ret2 = " << ret2 << std::endl; // 未知
	std::cout << "ret2 = " << ret2 << std::endl; // 未知
}