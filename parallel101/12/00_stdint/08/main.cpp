#include <cstdint>
#include <cstdio>
#include <type_traits>

int main()
{
    static_assert(std::is_same<decltype((unsigned short)3 + (int)3), int>::value, "小彭老师的断言");
    return 0;
}