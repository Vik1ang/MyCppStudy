#ifndef MYTINYSTL_CONSTRUCT_H_
#define MYTINYSTL_CONSTRUCT_H_

#define MYSTL_API __declspec(dllexport)

// 这个头文件包含两个函数 construct，destroy
// construct : 负责对象的构造
// destroy   : 负责对象的析构

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)  // unused parameter
#endif // _MSC_VER
#include <iterator>

namespace mystl
{
	// construct 构造对象
	template <class Ty>
	void construct(Ty* ptr);

	template <class Ty1, class Ty2>
	void construct(Ty1* ptr, const Ty2& value);

	template <class Ty, class...Args>
	void construct(Ty* ptr, Args&&...args);

	// destroy 将对象析构
	template <class Ty>
	void destroy_one(Ty*, std::true_type);

	template <class Ty>
	void destroy_one(Ty* pointer, std::false_type);

	template <class ForwardIter>
	void destroy_cat(ForwardIter, ForwardIter, std::true_type);

	template <class ForwardIter>
	void destroy_cat(ForwardIter first, ForwardIter last, std::false_type);

	template <class Ty>
	void destroy(Ty* pointer);

	template <class ForwardIter>
	void destroy(ForwardIter first, ForwardIter last);
} // namespace mystl

#endif // MYTINYSTL_CONSTRUCT_H_