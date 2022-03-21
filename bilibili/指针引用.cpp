#include <cstdlib>

struct Person
{
	int m_Age;
};

void allocateMemory(Person** p) // **p 具体的person对象  *p 对象的指针 p指针的指针
{
	*p = (Person*)malloc(sizeof(Person));
	(*p)->m_Age = 100;
}

void allocateMemoryByRef(Person*& p)
{
	p = (Person*)(sizeof(Person));
	p->m_Age = 100;
}

void test1()
{
	Person* p = NULL;
	allocateMemory(&p);
}

void test2() {
	Person* p = NULL;
	allocateMemoryByRef(p);
}

void main_func()
{
	test1();
}