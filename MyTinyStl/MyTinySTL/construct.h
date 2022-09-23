#ifndef MYTINYSTL_CONSTRUCT_H
#define MYTINYSTL_CONSTRUCT_H

// 这个头文件包含两个函数 construct，destroy
// construct : 负责对象的构造
// destroy   : 负责对象的析构

#include <new>

#ifdef _MSV_VER
#pragma warning(push)
#pragma warning(disable : 4100)  // unused parameter
#endif                           // _MSV_VER

namespace mystl {

// construct 构造对象

template <class Ty>
void construct(Ty *ptr) {
  ::new ((void *)ptr) Ty();
}

template <class Ty1, class Ty2>
void construct(Ty *ptr, const Ty2 &value) {
  ::new ((void *)ptr) Ty1(value)
}

template <class Ty, class... Args>
void construct(Ty *ptr, Args &&...args) {
  ::new ((void *)ptr) Ty(mystl::)  // FIXME
}

// destroy 对象析构
template <class Ty>
void destroy_one(Ty *, std::true_type) {}

template <class Ty>
void destroy_one(Ty *pointer, std::false_type) {
  if (pointer != nullptr) {
    pointer->~Ty();
  }
}

template <class ForwardIter>
void destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

template <class ForwardIter>
void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
  destroy_cat(first, last, std::is_trivially_destructible<typename iterator_traits<ForwardIter>::value_type>{})
}
}  // namespace mystl

#endif  // MYTINYSTL_CONSTRUCT_H
