#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <functional>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <stdexcept>

#include "helper.hpp"

void string_study()
{
	std::string str1; //默认构造
	std::string str2(str1);
	std::string str3 = str1;
	std::string str4 = "abcd";
	std::string str5(10, 'a');

	std::cout << str4 << std::endl;
	std::cout << str5 << std::endl;

	// 基本赋值
	str1 = "hello";
	str2 = str4;

	// assign
	str3.assign("abcdef", 4);
	std::cout << str3 << std::endl;

	std::string str6;
	str6.assign(str1, 1, 3);
	std::cout << str6 << std::endl;

	// 存取字符串操作
	str1 = "hello world";
	for (int i = 0; i < str1.size(); ++i)
	{
		std::cout << str1[i] << " ";
	}
	std::cout << std::endl;
	// [] at
	try
	{
		//std::cout << str1[100] << std::endl; // 捕获不到异常
		std::cout << str1.at(100) << std::endl;
	}
	catch (std::out_of_range& e)
	{
		std::cout << e.what() << std::endl;
	}

	// 字符串拼接
	str1.clear();
	str2.clear();
	str1 = "我";
	str2 = "爱北京";
	str1 += str2;
	str1.append("天安门");
	std::cout << str1 << std::endl;

	// 查找
	str1 = "abcdefg";
	int pos1 = str1.find("bc");
	std::cout << pos1 << std::endl;
	pos1 = str1.find("bce");
	std::cout << pos1 << std::endl;

	int pos2 = str1.rfind("bc");
	std::cout << pos2 << std::endl;

	// 替换
	str3.clear();
	str3 = "hello";
	str3.replace(1, 3, "111111");
	std::cout << str3 << std::endl;

	// 比较
	str1.clear();
	str2.clear();
	str1 = "abc";
	str2 = "aBc";
	std::cout << str1.compare(str2) << std::endl;

	// 字串
	str1.clear();
	str2.clear();
	str1 = "abcde";
	str2 = str1.substr(1, 3);
	std::cout << str2 << std::endl;

	// 插入
	str1.clear();
	str1 = "hello";
	str1.insert(1, "111");
	std::cout << str1 << std::endl;

	// 删除
	str1.erase(1, 3);
	std::cout << str1 << std::endl;

	// c-style转换
	str1.clear();
	str2.clear();
	str1 = "abc";
	const char* p = str1.c_str();
	str2 = std::string(p);
	std::cout << str2 << std::endl;

	// 练习
	std::string s = "abcdEfG";
	for (int i = 0; i < s.size(); ++i)
	{
		s[i] = std::toupper(s[i]);
	}
	std::cout << s << std::endl;
}

void vector_study()
{
	// 构造
	std::vector<int>v;
	int arr[] = { 1, 2, 3, 4, 5 };
	std::vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));
	std::vector<int> v2(v1.begin(), v1.end());
	helper::print_container(v2);
	std::vector<int> v3(10, 100);
	helper::print_container(v3);

	// 赋值
	std::vector<int> v4;
	v4.assign(v3.begin(), v3.end());
	helper::print_container(v4);
	v4.swap(v2);
	helper::print_container(v4);
	v4.resize(10);
	helper::print_container(v4);
	v4 = std::vector<int>(v1.begin(), v1.end());
	v4.resize(10, -1);
	helper::print_container(v4);

	// swap压缩空间
	helper::swap_resize_helper();

	// 存取
	v.clear();
	v.push_back(10);
	v.push_back(30);
	v.push_back(20);
	v.push_back(50);
	helper::print(v.front());
	helper::print(v.back());

	// 插入和删除
	v.insert(v.begin(), 100);
	helper::print_container(v);
	v.insert(v.begin(), 3, 100);
	helper::print_container(v);
	v.pop_back();
	helper::print_container(v);
	v.erase(v.begin());
	helper::print_container(v);
	v.erase(v.begin(), v.end());
	helper::print(v.empty());

	// 逆序遍历
	v.clear();
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	helper::print_container(v);
	helper::print_vector_reverse(v);
}

void deque_study()
{
	std::deque<int> d;

	d.push_back(10);
	d.push_back(40);
	d.push_back(30);
	d.push_back(20);
	helper::print_container(d);

	std::deque<int> d2(d.begin(), d.end());
	d2.push_back(10000);

	d.swap(d2);
	helper::print_container(d);

	d.clear();
	d.push_back(10);
	d.push_back(30);
	d.push_back(20);
	d.push_front(100);
	d.push_front(200);
	helper::print_container(d);

	d.pop_back();
	d.pop_front();
	helper::print_container(d);

	helper::print(d.front());
	helper::print(d.back());

	d2.clear();
	d2.push_back(50);
	d2.push_back(60);
	d2.insert(d2.begin(), d.begin(), d.end());
	helper::print_container(d2);
}

void stack_study()
{
	std::stack<int> s;
	s.push(10);
	s.push(30);
	s.push(20);
	s.push(40);

	//helper::print_container(s);
}

void queue_study()
{
	std::queue<int> q;
	q.push(10);
	q.push(20);
	q.push(30);
	q.push(40);
	//helper::print_container(q);
}

void list_study()
{
	std::list<int> l(10, 10);
	helper::print_container(l);
	std::list<int> l2(l.begin(), l.end());
	helper::print_container(l2);
}

void set_study()
{
	std::set<int> s1;
	s1.insert(5);
	s1.insert(1);
	s1.insert(9);
	s1.insert(3);
	s1.insert(7);

	helper::print_container(s1);

	s1.erase(s1.begin());
	helper::print_container(s1);
	s1.erase(5);
	helper::print_container(s1);

	std::set<int>::iterator pos = s1.find(7);
	if (pos != s1.end())
		helper::print(*pos);
	else
		helper::print("未找到");
	s1.insert(7);
	helper::print(s1.count(7));
}

void function_object()
{
	function_object_helper::MyPrint my_print;
	my_print(111);
	function_object_helper::MyPrint()(10000);

	function_object_helper::MyPrint my_print1;
	my_print1(111);
	my_print1(111);
	my_print1(111);
	my_print1(111);
	std::cout << "myprint使用次数: " << my_print1.count << std::endl;

	function_object_helper::do_print(function_object_helper::MyPrint(), 20);
}

void predicate_study()
{
	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	// 查找第一个大于20的
	std::vector<int>::iterator pos = std::find_if(v.begin(), v.end(), predicate_helper::GreaterThan20());
	if (pos != v.end())
	{
		std::cout << "找到大于20" << std::endl;
	}
	else
	{
		std::cout << "没找到" << std::endl;
	}

	v.clear();
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	std::sort(v.begin(), v.end(), predicate_helper::MyCompare());

	std::for_each(v.begin(), v.end(), [](int val)
		{
			std::cout << val << " ";
		});
	std::cout << std::endl;
}

void builtin_function_study()
{
	// 取反
	std::negate<int>n;
	std::cout << n(10) << std::endl;
	// 加法
	std::plus<int>p;
	std::cout << p(1, 1) << std::endl;

	std::vector<int>v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	std::sort(v.begin(), v.end(), std::greater<int>());
	std::for_each(v.begin(), v.end(), [](int val) {std::cout << val << " "; });
	std::cout << std::endl;
}

void adapter_study()
{
	std::vector<int> v;
	v.reserve(10);
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	const int num = 5;
	std::for_each(v.begin(), v.end(), std::bind2nd(adapter_helper::MyPrint(), num));
	std::for_each(v.begin(), v.end(), std::bind1st(adapter_helper::MyPrint(), num));

	v.clear();
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}

	std::vector<int>::iterator pos = std::find_if(v.begin(), v.end(), std::not1(adapter_helper::GreaterThan5()));
	if (pos != v.end())
	{
		std::cout << "找到了小于5" << std::endl;
	}
	else
	{
		std::cout << "未找到" << std::endl;
	}

	v.clear();
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}

	const auto pos1 = std::find_if(
		v.begin(),
		v.end(),
		std::not1(std::bind2nd(std::greater<int>(), 5))
	);
	if (pos1 != v.end())
	{
		std::cout << "找到了小于5" << std::endl;
	}
	else
	{
		std::cout << "未找到" << std::endl;
	}

	v.clear();
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	std::for_each(v.begin(), v.end(), std::bind2nd(std::ptr_fun(adapter_helper::MyPrint3), 100));

	adapter_helper::Person p1("aaa", 10);
	adapter_helper::Person p2("bbb", 15);
	adapter_helper::Person p3("ccc", 18);
	adapter_helper::Person p4("ddd", 40);

	std::vector<adapter_helper::Person>v1;
	v1.push_back(p1);
	v1.push_back(p2);
	v1.push_back(p3);
	v1.push_back(p4);

	std::for_each(v1.begin(), v1.end(), adapter_helper::MyPrintPerson);
	std::for_each(v1.begin(), v1.end(), std::mem_fun_ref(&adapter_helper::Person::show_person));
	std::for_each(v1.begin(), v1.end(), std::mem_fun_ref(&adapter_helper::Person::plus_age));
	std::for_each(v1.begin(), v1.end(), std::mem_fun_ref(&adapter_helper::Person::show_person));
}

void traverse_study()
{
}

int main(int argc, char* argv[])
{
	helper::print("********string********");
	string_study();
	helper::print("********vector********");
	vector_study();
	helper::print("********deque********");
	deque_study();
	helper::print("********stack********");
	stack_study();
	helper::print("********queue********");
	queue_study();
	helper::print("********list********");
	list_study();
	helper::print("********set********");
	set_study();

	helper::print("********algorithm********");

	helper::print("********函数对象********");
	function_object();
	helper::print("********谓词********");
	predicate_study();
	helper::print("********内建函数对象********");
	builtin_function_study();
	helper::print("********适配器********");
	adapter_study();
	helper::print("********遍历********");
	traverse_study();
	return EXIT_SUCCESS;
}