#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. 全局变量增强
// 编译通过
int a;
int a = 10;

// 2. 函数检测增强
int get_rect_area(w, h) {}

void test02()
{
	get_rect_area(10, 10, 10);
}

// 3. 类型转换检测增强
void test3()
{
	char* p = malloc(sizeof(64)); // malloc返回值是void*
}

// 4. struct增强
struct person
{
	int m_age;
	//void plus_age(); // c语言中 struct不能加入函数
};

void test04()
{
	struct person p1; // 使用时候必须加入struct关键字
}

// 5. bool类型增强
//bool flag; // c语言没有bool类型

// 6. 三目运算符增强
void test06()
{
	int a = 10;
	int b = 20;

	printf("res = %d\n", a > b ? a : b);
}

int main_func(int argc, char* argv[])
{
	return EXIT_SUCCESS;
}