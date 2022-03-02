#include <iostream>
using namespace std;

// 1. 全局变量增强
int a;
//int a = 10; // 编译不通过

// 2. 函数检测增强, 参数类型增强
//int get_rect_area(w, h){} // 编译不通过
//int get_rect_area(w, h) {}
//void test02()
//{
//	get_rect_area(10, 10, 10);
//}
int get_rect_area(int width, int height)
{
	return width * height;
}

void test2()
{
	get_rect_area(10, 10);
};

// 3. 类型转换检测增强
void test3()
{
	char* p = (char*)malloc(sizeof(64)); // malloc返回值是void*
}

// 4. struct增强
struct person
{
	int m_age;
	void plus_age(); // c语言中 struct不能加入函数, cpp可以
};

void test04()
{
	person p1; // 可以不加入struct关键字
	p1.m_age = 10;
	p1.plus_age();
}

// 5. bool类型增强
bool flag;

// 6. 三目运算符增强
void test06()
{
	int a = 10;
	int b = 20;

	cout << "res = " << (a > b ? a : b) << endl;
}

void test05()
{
	cout << sizeof(bool) << endl;
	flag = 100;
	cout << flag << endl;
}
int main_func(int argc, char* argv[])
{
	return EXIT_SUCCESS;
}