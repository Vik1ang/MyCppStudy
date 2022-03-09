#include <iostream>
const double pi = 3.14;

// 1. 设计一个类, 求圆的周长
class Circle
{
public:
	// 半径
	int m_R;

	void setR(int r)
	{
		m_R = r;
	}

	double calculateZC()
	{
		return 2 * pi * m_R;
	}
};

void test1()
{
	Circle c1;
	c1.m_R = 10;

	std::cout << "c1的周长: " << c1.calculateZC() << std::endl;
}

class Student
{
public:
	std::string m_Name;
	int m_Id;

	void setName(std::string name)
	{
		m_Name = name;
	}

	void setId(int id)
	{
		m_Id = id;
	}
};

void test2()
{
	Student stu;
	stu.setName("123");
	stu.setId(123);
}

void main_func()
{
	test1();
	test2();
}