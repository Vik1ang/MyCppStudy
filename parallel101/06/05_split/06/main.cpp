#include "mtprint.h"
#include "ticktock.h"
#include <cmath>
#include <iostream>
#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for.h>
#include <thread>
#include <vector>

int main()
{
    size_t n = 1 << 14;
    std::vector<float> a(n * n);
    std::vector<float> b(n * n);

    TICK(transpose);
    tbb::parallel_for(tbb::blocked_range2d<size_t>(0, n, 0, n),
        [&](tbb::blocked_range2d<size_t> r) {
            for (size_t i = r.cols().begin(); i < r.cols().end(); i++) {
                for (size_t j = r.rows().begin(); j < r.rows().end(); j++) {
                    b[i * n + j] = a[j * n + i];
                }
            }
        });
    TOCK(transpose);

    return 0;
}