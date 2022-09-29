#include "ticktock.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <vector>

int main()
{
    size_t n = 1 << 27;
    std::vector<float> a(n);

    TICK(for);
    // fill a with sin(i)
    for (size_t i = 0; i < a.size(); i++) {
        a[i] = std::sin(i);
    }
    TOCK(for);

    TICK(reduce);
    // calculate sum of a
    float res = 0;
    for (size_t i = 0; i < a.size(); i++) {
        res += a[i];
    }
    TOCK(reduce);

    std::cout << res << std::endl;
    return 0;
}