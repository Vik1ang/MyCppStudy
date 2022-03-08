#include <iostream>

void test01()
{
	int a = 10;
	int& b = a;

	b = 20;

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
}

// 2. 引用必须初始化
void test02()
{
	// int &a; // 必须初始化
	int a = 10;
	int& b = a; // 引用初始化后不可以修改

	int c = 20;
	b = c; // 赋值
}

// 3. 对数组建立引用
void test03()
{
	int arr[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i;
	}

	// 数组起别名
	int(&pArr)[10] = arr;

	for (int i = 0; i < 10; i++)
	{
		std::cout << pArr[i] << " ";
	}

	std::cout << std::endl;

	// 第二种方式 起别名
	typedef int(ARRAYREF)[10];
	ARRAYREF& pArr2 = arr;
	for (int i = 0; i < 10; i++)
	{
		std::cout << pArr2[i] << " ";
	}
}