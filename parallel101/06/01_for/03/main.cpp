#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <vector>

int main()
{
    size_t n = 1 << 26;
    std::vector<float> a(n);

    tbb::parallel_for(tbb::blocked_range<size_t>(0, n), [&](tbb::blocked_range<size_t> r) {
        for (size_t i = r.begin(); i < r.end(); i++) {
            a[i] = std::sin(i);
        }
    });

    return 0;
}