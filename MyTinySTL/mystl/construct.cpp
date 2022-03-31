#include "pch.h"

#include "include/construct.h"

template <class Ty>
void mystl::construct(Ty* ptr)
{
	::new(static_cast<void*>(ptr)) Ty();
}

template <class Ty1, class Ty2>
void mystl::construct(Ty1* ptr, const Ty2& value)
{
	::new(static_cast<void*>(ptr)) Ty1(value);
}

template <class Ty, class ... Args>
void mystl::construct(Ty* ptr, Args&&... args)
{
	// TODO: 现在还没用上
}

template <class Ty>
void mystl::destroy_one(Ty*, std::true_type) {}

template <class Ty>
void mystl::destroy_one(Ty* pointer, std::false_type)
{
	if (pointer != nullptr)
	{
		pointer->~Ty();
	}
}

template <class ForwardIter>
void mystl::destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

template <class ForwardIter>
void mystl::destroy_cat(ForwardIter first, ForwardIter last, std::false_type)
{
	for (; first != last; ++first)
	{
		destroy(&*first);
	}
}

template <class Ty>
void mystl::destroy(Ty* pointer)
{
	destroy_one(pointer, std::is_trivially_destructible<Ty>{});
}

template <class ForwardIter>
void mystl::destroy(ForwardIter first, ForwardIter last)
{
	destroy_cat(first, last, std::is_trivially_destructible<
		typename std::iterator_traits<ForwardIter>::value_type>{});
}