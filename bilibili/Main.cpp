#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <deque>
#include <functional>
#include <list>
#include <numeric>
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
	helper::println(v.front());
	helper::println(v.back());

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
	helper::println(v.empty());

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

	helper::println(d.front());
	helper::println(d.back());

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
	std::list<int> l1(10, 10);
	std::list<int> l2(l1.begin(), l1.end());
	helper::print_container(l1);
	helper::print_container(l2);

	std::list<int> l3;
	l3.push_back(10);
	l3.push_back(30);
	l3.push_back(20);
	l3.push_front(100);
	l3.push_front(200);
	l3.push_front(300);
	helper::print_container(l3);
	l3.pop_front();
	l3.pop_back();
	helper::print_container(l3);
	l3.insert(l3.begin(), 1000);
	helper::print_container(l3);

	l3.remove(10);
	helper::print_container(l3);

	l3.clear();
	l3.push_back(10);
	l3.push_back(30);
	l3.push_back(20);
	l3.push_front(100);
	l3.push_front(200);
	l3.push_front(300);

	std::list<int> l4;
	l4.push_back(10);
	l4.push_back(20);
	l4.push_back(40);
	l4.push_back(30);
	l4.reverse();
	helper::print_container(l4);
	l4.sort();
	helper::print_container(l4);
	l4.sort(list_helper::my_compare);
	helper::print_container(l4);

	std::list<list_helper::Person>l5;
	list_helper::Person p1("aaa", 10);
	list_helper::Person p2("bbb", 20);
	list_helper::Person p3("ccc", 17);
	list_helper::Person p4("ddd", 19);
	list_helper::Person p5("eee", 18);
	l5.push_back(p1);
	l5.push_back(p2);
	l5.push_back(p3);
	l5.push_back(p4);
	l5.push_back(p5);
	l5.sort(list_helper::my_compare_person);
	for (const auto& person : l5)
	{
		std::cout << "Name: " << person.m_Name << " Age: " << person.m_Age;
	}
	std::cout << std::endl;
	l5.remove(p1);
	for (const auto& person : l5)
	{
		std::cout << "Name: " << person.m_Name << " Age: " << person.m_Age;
	}
	std::cout << std::endl;
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
		helper::println(*pos);
	else
		helper::println("未找到");
	s1.insert(7);
	helper::println(s1.count(7));
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
	std::vector<int> v;
	v.reserve(10);
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}

	std::for_each(v.begin(), v.end(), traverse_helper::my_print);
	std::for_each(v.begin(), v.end(), traverse_helper::MyPrint1());

	const traverse_helper::MyPrint2 my_print2 = std::for_each(v.begin(), v.end(), traverse_helper::MyPrint2());
	std::cout << my_print2.m_Count << std::endl;

	v.clear();
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}

	std::for_each(v.begin(), v.end(), std::bind2nd(traverse_helper::my_print3(), 10000));

	v.clear();
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	std::vector<int> v_target;

	v_target.resize(v.size());
	std::transform(v.begin(), v.end(), v_target.begin(), traverse_helper::TransFrom());
	std::for_each(v_target.begin(), v_target.end(), [](const int val) {std::cout << val << " "; });
	std::cout << std::endl;

	std::vector<int> v1;
	std::vector<int> v2;
	std::vector<int> v_target1;
	for (int i = 0; i < 10; ++i)
	{
		v1.push_back(i + 100);
		v2.push_back(i + 200);
	}
	v_target1.resize(v1.size());
	std::transform(v1.begin(), v1.end(), v2.begin(), v_target1.begin(), traverse_helper::TransFrom2());
	std::for_each(v_target.begin(), v_target.end(), [](const int val) {std::cout << val << " "; });
	std::cout << std::endl;
}

void find_study()
{
	std::vector<int> v;
	v.reserve(10);
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	std::vector<int>::iterator pos = std::find(v.begin(), v.end(), 5);
	if (pos != v.end())
	{
		std::cout << "找到了" << std::endl;
	}
	else
	{
		std::cout << "没找到" << std::endl;
	}

	std::vector<find_helper::Person> v_person;
	find_helper::Person p1("aaa", 10);
	find_helper::Person p2("bbb", 20);
	find_helper::Person p3("ccc", 30);
	find_helper::Person p4("ddd", 40);
	v_person.push_back(p1);
	v_person.push_back(p2);
	v_person.push_back(p3);
	v_person.push_back(p4);

	auto pos1 = std::find(v_person.begin(), v_person.end(), p2);
	if (pos1 != v_person.end())
	{
		std::cout << "找到了" << std::endl;
	}
	else
	{
		std::cout << "没找到" << std::endl;
	}

	std::vector<find_helper::Person*> v_person_ptr;
	find_helper::Person p1_ptr("aaa", 10);
	find_helper::Person p2_ptr("bbb", 20);
	find_helper::Person p3_ptr("ccc", 30);
	find_helper::Person p4_ptr("ddd", 40);
	v_person_ptr.push_back(&p1_ptr);
	v_person_ptr.push_back(&p2_ptr);
	v_person_ptr.push_back(&p3_ptr);
	v_person_ptr.push_back(&p4_ptr);

	auto p_ptr = new find_helper::Person("bbb", 21);
	std::find(v_person_ptr.begin(), v_person_ptr.end(), p_ptr);
	auto pos2 = std::find_if(
		v_person_ptr.begin(),
		v_person_ptr.end(),
		std::bind2nd(find_helper::MyCompare(), p_ptr)
	);
	if (pos2 != v_person_ptr.end())
	{
		std::cout << "找到了" << std::endl;
	}
	else
	{
		std::cout << "没找到" << std::endl;
	}

	v.clear();
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(5);
	v.push_back(6);
	v.push_back(2);

	auto pos3 = std::adjacent_find(v.begin(), v.end());
	if (pos3 != v.end())
	{
		std::cout << *pos3 << std::endl;
	}
	else
	{
		std::cout << "没找到" << std::endl;
	}

	v.clear();
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	bool ret = std::binary_search(v.begin(), v.end(), 4);
	if (ret)
	{
		std::cout << "找到了" << std::endl;
	}
	else
	{
		std::cout << "没找到" << std::endl;
	}

	v.clear();
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	v.push_back(4);
	v.push_back(4);
	v.push_back(4);
	v.push_back(4);
	v.push_back(4);

	ptrdiff_t count = std::count(v.begin(), v.end(), 4);
	std::cout << "4的个数为" << count << std::endl;

	count = std::count_if(v.begin(), v.end(), find_helper::GreaterThan4());
	std::cout << "大于4的个数为" << count << std::endl;
}

void sort_study()
{
	std::vector<int>v1;
	std::vector<int>v2;

	for (int i = 0; i < 10; ++i)
	{
		v1.push_back(i);
		v2.push_back(i + 1);
	}

	std::vector<int> v_target;
	v_target.resize(v1.size() + v2.size());
	std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin());
	std::for_each(v_target.begin(), v_target.end(), [](const int val) { std::cout << val << " "; });
	std::cout << std::endl;

	v1.clear();
	v1.push_back(10);
	v1.push_back(40);
	v1.push_back(20);
	v1.push_back(90);
	v1.push_back(50);

	std::sort(v1.begin(), v1.end());
	helper::print_container(v1);

	std::sort(v1.begin(), v1.end(), std::greater<int>());
	helper::print_container(v1);

	v1.clear();
	for (int i = 0; i < 10; ++i)
	{
		v1.push_back(i);
	}
	//std::random_shuffle(v1.begin(), v1.end());
	std::shuffle(v1.begin(), v1.end(), std::mt19937(std::random_device()()));
	helper::print_container(v1);

	v1.clear();
	for (int i = 0; i < 10; ++i)
	{
		v1.push_back(i);
	}
	std::reverse(v1.begin(), v1.end());
	helper::print_container(v1);
}

void copy_replace_study()
{
	std::vector<int> v;
	v.reserve(10);
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	std::vector<int> v_target;
	v_target.resize(v.size());

	std::copy(v.begin(), v.end(), v_target.begin());
	helper::print_container(v_target);

	v.clear();
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	std::replace(v.begin(), v.end(), 3, 300);
	helper::print_container(v);

	v.clear();
	v.clear();
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	std::replace_if(v.begin(), v.end(), copy_replace_helper::MyCompare(), 30000);
	helper::print_container(v);

	std::vector<int> v1;
	for (int i = 0; i < 10; ++i)
	{
		v1.push_back(i);
	}
	std::vector<int> v2;
	v2.push_back(10);
	v2.push_back(30);
	v2.push_back(20);
	v2.push_back(40);
	helper::println("交换前");
	helper::print_container(v1);
	helper::print_container(v2);
	std::swap(v1, v2);
	helper::println("交换后");
	helper::print_container(v1);
	helper::print_container(v2);
}

void arithmetic_generation_study()
{
	std::vector<int> v;
	for (int i = 0; i <= 100; ++i)
	{
		v.push_back(i);
	}
	int sum = std::accumulate(v.begin(), v.end(), 1000);
	helper::println(sum);

	v.clear();
	v.resize(10);
	std::fill(v.begin(), v.end(), 1000);
	helper::print_container(v);
}

void collections_study()
{
	std::vector<int> v1;
	std::vector<int> v2;
	for (int i = 0; i < 10; ++i)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}
	std::vector<int> v_target;
	v_target.resize(std::min(v1.size(), v2.size()));
	const std::vector<int>::iterator it_end = std::set_intersection(
		v1.begin(),
		v1.end(),
		v2.begin(),
		v2.end(),
		v_target.begin()
	);
	std::for_each(v_target.begin(), it_end, [](const int val) {helper::print(val); });
	std::cout << std::endl;

	v_target.clear();
	v_target.resize(v1.size() + v2.size());
	auto it_end1 = std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin());
	std::for_each(v_target.begin(), it_end1, [](const int val) {helper::print(val); });
	std::cout << std::endl;

	v_target.clear();
	v_target.resize(std::max(v1.size(), v2.size()));
	auto it_end2 = std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin());
	std::for_each(v_target.begin(), it_end2, [](const int val) {helper::print(val); });
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	{
		helper::println("********string********");
		string_study();
		helper::println("********vector********");
		vector_study();
		helper::println("********deque********");
		deque_study();
		helper::println("********stack********");
		stack_study();
		helper::println("********queue********");
		queue_study();
		helper::println("********list********");
		list_study();
		helper::println("********set********");
		set_study();
	}
	/*{
		helper::println("********algorithm********");

		helper::println("********函数对象********");
		function_object();
		helper::println("********谓词********");
		predicate_study();
		helper::println("********内建函数对象********");
		builtin_function_study();
		helper::println("********适配器********");
		adapter_study();
		helper::println("********遍历********");
		traverse_study();
		helper::println("********查找********");
		find_study();
		helper::println("********排序********");
		sort_study();
		helper::println("********拷贝和替换********");
		copy_replace_study();
		helper::println("********算数生成********");
		arithmetic_generation_study();
		helper::println("********集合算法********");
		collections_study();
	}*/
	return EXIT_SUCCESS;
}