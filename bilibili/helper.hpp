#pragma once
#include <iostream>
#include <ostream>
#include <vector>

namespace helper
{
	template<typename T>
	void print_container(const T& v)
	{
		for (const auto value : v)
		{
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

	template<typename T>
	void print_vector_reverse(const std::vector<T>& v)
	{
		for (auto it = v.rbegin(); it != v.rend(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	void swap_resize_helper()
	{
		std::vector<int> v;
		for (int i = 0; i < 10000; ++i)
		{
			v.push_back(i);
		}
		std::cout << "v的容量" << v.capacity() << std::endl;
		std::cout << "v的大小" << v.size() << std::endl;

		v.resize(3);

		std::cout << "v的容量" << v.capacity() << std::endl;
		std::cout << "v的大小" << v.size() << std::endl;

		v.shrink_to_fit();
		//std::vector<int>(v).swap(v);

		std::cout << "v的容量" << v.capacity() << std::endl;
		std::cout << "v的大小" << v.size() << std::endl;
	}

	template<typename T>
	void print(T v)
	{
		std::cout << v << std::endl;
	}
}

namespace function_object_helper
{
	class MyPrint
	{
	public:
		void operator()(int num)
		{
			std::cout << "num=" << num << std::endl;
			count++;
		}
		int count = 0;
	};

	inline void do_print(MyPrint print, int num)
	{
		print(num);
	}
}

namespace predicate_helper
{
	class GreaterThan20
	{
	public:
		bool operator()(int val) const
		{
			return val > 20;
		}
	};

	class MyCompare
	{
	public:
		bool operator()(int val1, int val2) const
		{
			return val1 > val2;
		}
	};
}

namespace adapter_helper
{
	class MyPrint :public std::binary_function<int, int, void>
	{
	public:
		void operator()(const int v, const int start) const
		{
			std::cout << "v = " << v << " start = " << start << " v + start = " << v + start << std::endl;
		}
	};

	class GreaterThan5 : public std::unary_function<int, bool>
	{
	public:
		bool operator()(int v) const
		{
			return v > 5;
		}
	};

	inline void MyPrint3(const int v, const int start)
	{
		std::cout << v + start << std::endl;
	}

	class Person
	{
	public:
		Person(std::string name, int age) : m_Name(std::move(name)), age(age)
		{
		}

		void show_person() const
		{
			std::cout << m_Name << " " << age << std::endl;
		}

		void plus_age()
		{
			this->age += 100;
		}

		std::string m_Name;
		int age;
	};

	inline void MyPrintPerson(const Person& p)
	{
		std::cout << p.m_Name << " " << p.age << std::endl;
	}
}

namespace traverse_helper
{
	inline void my_print(const int v)
	{
		std::cout << v << std::endl;
	}

	class MyPrint1
	{
	public:
		void operator()(int v) const
		{
			std::cout << v << std::endl;
		}
	};

	class MyPrint2
	{
	public:
		void operator()(const int v)
		{
			std::cout << v << std::endl;
			m_Count++;
		}
		int m_Count;
	};

	struct my_print3 : std::binary_function<int, int, void>
	{
		void operator()(const int v, const int start) const
		{
			std::cout << v + start << std::endl;
		}
	};

	class TransFrom
	{
	public:
		int operator()(const int val) const
		{
			return val + 10;
		}
	};

	class TransFrom2
	{
	public:
		int operator()(const int val1, const int val2) const
		{
			return val1 + val2;
		}
	};
}

namespace find_helper
{
	class Person
	{
	public:
		Person(const std::string name, const int age) : m_Name(name), m_Age(age)
		{
		}
		bool operator==(const Person& p) const
		{
			if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
			{
				return true;
			}
			return false;
		}

		std::string m_Name;
		int m_Age;
	};

	class MyCompare : public std::binary_function<Person*, Person*, bool>
	{
	public:
		bool operator()(const Person* p1, const Person* p2) const
		{
			if (p1->m_Name == p2->m_Name && p1->m_Age == p2->m_Age)
			{
				return true;
			}
			return false;
		}
	};

	class GreaterThan4
	{
	public:
		bool operator()(const int val) const
		{
			return val > 4;
		}
	};
}