#include <iostream>

template <class Func>
void call_twice(Func func)
{
    std::cout << func(0) << std::endl;
    std::cout << func(1) << std::endl;
}

int main()
{
    int fac = 2;
    auto twice = [&] (int n) {
        return n * fac;  // 返回类型自动推导为 int
    };
    call_twice(twice);

    return 0;
}