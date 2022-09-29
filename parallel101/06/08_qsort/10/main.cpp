#include "ticktock.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <tbb/parallel_invoke.h>
#include <vector>

template <class T>
T quick_reduce(T* data, size_t size)
{
    if (size < (1 << 16)) {
        return std::reduce(data, data + size);
    }
    T sum1, sum2;
    size_t mid = size / 2;
    tbb::parallel_invoke([&] { sum1 = quick_reduce(data, mid); }, [&] { sum2 = quick_reduce(data + mid, size - mid); });
    return sum1 + sum2;
}

int main()
{
    size_t n = 1 << 25;
    std::vector<int> arr(n);
    std::generate(arr.begin(), arr.end(), std::rand);
    TICK(quick_reduce);
    int sum = quick_reduce(arr.data(), arr.size());
    TOCK(quick_reduce);
    printf("%d\n", sum);
    return 0;
}