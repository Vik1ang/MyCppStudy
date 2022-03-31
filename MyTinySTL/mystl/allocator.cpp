#include "pch.h"
#include "include/allocator.h"

#include <iostream>

template <class T>
T* mystl::allocator<T>::allocate()
{
	return static_cast<T*>(::operator new(sizeof(T)));
}

template <class T>
T* mystl::allocator<T>::allocate(size_type n)
{
	if (n == 0)
	{
		return nullptr;
	}
	return static_cast<T*>(::operator new(n * sizeof(T)));
}
	
template <class T>
void mystl::allocator<T>::deallocate(T* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	::operator delete(ptr);
}

template <class T>
void mystl::allocator<T>::deallocate(T* ptr, size_type)
{
	if (ptr == nullptr)
	{
		return;
	}
	::operator delete(ptr);
}

template <class T>
void mystl::allocator<T>::construct(T* ptr)
{
	// TODO: 现在还没用上
}

template <class T>
void mystl::allocator<T>::construct(T* ptr, const T& value)
{
	// TODO: 现在还没用上
}

template <class T>
void mystl::allocator<T>::construct(T* ptr, T&& value)
{
	// TODO: 现在还没用上
}

template <class T>
template <class ... Args>
void mystl::allocator<T>::construct(T* ptr, Args&&... args)
{
	// TODO: 现在还没用上
}

template <class T>
void mystl::allocator<T>::destroy(T* ptr)
{
	// TODO: 现在还没用上
}

template <class T>
void mystl::allocator<T>::destroy(T* first, T* last)
{
	// TODO: 现在还没用上
}


void mystl::A::print()
{
	std::cout << "abc\n";
}
