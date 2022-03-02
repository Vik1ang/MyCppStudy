#include "game1.h"
#include "game2.h"

// namespace命名空间主要用途 用来解决命名冲突问题

// 1. 命名空间下可以放 函数, 变量, 结构体, 类
// 2. 命名空间必须定义在全局作用域下
// 3. 命名空间可以嵌套命名空间
// 4. 命名空间是开放的, 可以随时往原先的命名空间添加内容
// 5. 匿名空间 => 相当于 static
// 6. 别名
namespace a
{
	void func();
	int m_a;
	struct person {};
	class animal {};

	namespace b
	{
		int m_a;
	}
}

void test01()
{
	lol::go_atk();
	wzry::go_atk();
}

void test02()
{
	cout << "作用域b下的m_a" << a::b::m_a << endl;
}

namespace a
{
	int m_b = 1;
}

void test03()
{
	cout << a::m_a << endl;
	cout << a::m_b << endl;
}

namespace
{
	int m_c = 0; // => int static m_c = 0;
	int m_d = 0; // => int static m_d = 0;
}

namespace special_name
{
	int m_a = 0;
}

void test04()
{
	namespace another_name = special_name;
	cout << special_name::m_a << endl;
	cout << another_name::m_a << endl;
}

int main_func(int argc, char* argv[])
{
	test01();
	test02();
	return EXIT_SUCCESS;
}