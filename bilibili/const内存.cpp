#include <iostream>
#include <string>
using namespace std;

// 1. const 分配内存, 取地址会分配临时内存
// 2. extern编译器也会给const变量分配内存
void test01()
{
	const int m_A = 10;
	int* p = (int*)&m_A;
}

// 3. 用变量初始化 const 的变量
void test02()
{
	int a = 10;
	const int b = a; // 会分配内存

	int* p = (int*)&b;
	*p = 1000;

	cout << "b = " << b << endl;
}

// 4. 自定义数据类型, 加const也会分配内存
struct Person
{
	string m_Name;
	int m_Age;
};

void test03()
{
	Person p1;
	//p1.m_Name = "aaa";
	Person* p = (Person*)&p1;
	p->m_Name = "m_Name";
	(*p).m_Age = 18;

	cout << "姓名:" << p1.m_Name << " 年龄: " << p1.m_Age << endl;
}