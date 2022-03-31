#ifndef MYTINYSTL_ALLOCATOR_H_
#define MYTINYSTL_ALLOCATOR_H_

#define MYSTL_API __declspec(dllexport)

namespace mystl
{
	// 模板类：allocator
	// 模板函数代表数据类型
	template <class T>
	class MYSTL_API allocator
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

	public:
		static T* allocate();
		static T* allocate(size_type n);

		static void deallocate(T* ptr);
		static void deallocate(T* ptr, size_type n);

		static void construct(T* ptr);
		static void construct(T* ptr, const T& value);
		static void construct(T* ptr, T&& value);

		template <class... Args>
		static void construct(T* ptr, Args&& ...args);

		static void destroy(T* ptr);
		static void destroy(T* first, T* last);
	};

	class MYSTL_API A
	{
	public:
		static void print();
	};
} // namespace mystl

#endif  // MYTINYSTL_ALLOCATOR_H_