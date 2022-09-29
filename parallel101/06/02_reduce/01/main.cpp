#include <cmath>
#include <iostream>
#include <vector>

int main()
{
    size_t n = 1 << 26;
    float res = 0;

    for (size_t i = 0; i < n; i++) {
        res += std::sin(i);
    }

    std::cout << res << std::endl;
    return 0;
}