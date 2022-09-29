#include <cmath>
#include <iostream>
#include <tbb/concurrent_vector.h>
#include <tbb/parallel_for.h>
#include <vector>

int main()
{
    size_t n = 1 << 10;
    tbb::concurrent_vector<float> a;

    for (size_t i = 0; i < a.size(); i++) {
        a[i] += 1.0f;
    }

    std::cout << a[1] << std::endl;

    return 0;
}