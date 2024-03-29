#include "ticktock.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <tbb/parallel_for_each.h>
#include <vector>

struct Data {
    std::vector<float> arr;

    Data()
    {
        arr.resize(std::rand() % 100 * 500 + 10000);
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = std::rand() * (1.f / (float)RAND_MAX);
        }
    }

    void step1()
    {
        for (int i = 0; i < arr.size(); i++) {
            arr[i] += 3.14f;
        }
    }

    void step2()
    {
        std::vector<float> tmp(arr.size());
        for (int i = 1; i < arr.size() - 1; i++) {
            tmp[i] = arr[i - 1] + arr[i] + arr[i + 1];
        }
        std::swap(tmp, arr);
    }

    void step3()
    {
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = std::sqrt(std::abs(arr[i]));
        }
    }

    void step4()
    {
        std::vector<float> tmp(arr.size());
        for (int i = 1; i < arr.size() - 1; i++) {
            tmp[i] = arr[i - 1] - 2 * arr[i] + arr[i + 1];
        }
        std::swap(tmp, arr);
    }
};

int main()
{
    size_t n = 1 << 11;

    std::vector<Data> dats(n);

    TICK(process);
    tbb::parallel_for_each(dats.begin(), dats.end(), [&](Data& dat) {
        dat.step1();
        dat.step2();
        dat.step3();
        dat.step4();
    });
    TOCK(process);

    return 0;
}