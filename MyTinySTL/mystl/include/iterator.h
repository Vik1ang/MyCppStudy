#ifndef MYTINYSTL_ITERATOR_H_
#define MYTINYSTL_ITERATOR_H_

#define MYSTL_API __declspec(dllexport)

// 这个头文件用于迭代器设计，包含了一些模板结构体与全局函数

namespace mystl
{
	// 五种迭代器类型
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	// iterator模板
	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Distance difference_type;
	};

	// iterator traits

}

#endif
