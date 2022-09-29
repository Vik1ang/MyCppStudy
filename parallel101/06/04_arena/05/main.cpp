#include <cstddef>
#include <iostream>
#include <mutex>
#include <tbb/parallel_for.h>
#include <tbb/task.h>
#include <vector>
#include <cmath>

int main()
{
    size_t n = 1 << 13;
    std::vector<float> a(n * n);
    std::mutex mtx;

    tbb::parallel_for((size_t)0, (size_t)n, [&](size_t i) {
        std::lock_guard lck(mtx);
        tbb::task_arena ta;
        ta.execute([&] {
            tbb::parallel_for((size_t)0, (size_t)n, [&](size_t j) {
                a[i * n + j] = std::sin(i) * std::sin(j);
            });
        });
    });

    return 0;
}