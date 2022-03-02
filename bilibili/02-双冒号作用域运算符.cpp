#define CRI_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int atk = 200;
void test01()
{
	int atk = 100;
	cout << "攻击力为 : " << atk << endl;

	// 双冒号 作用域运算符
	cout << "全局攻击力为 : " << ::atk << endl;
}

int main_func(int argc, char* argv[])
{
	test01();
	cout << "Hello World" << endl;

	return EXIT_SUCCESS;
}