#include "ticktock.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <tbb/parallel_invoke.h>

int fib(int n)
{
    if (n < 2)
        return n;
    int first, second;
    tbb::parallel_invoke([&] { first = fib(n - 1); }, [&] { second = fib(n - 2); });
    return first + second;
}

int main()
{
    TICK(fib);
    std::cout << fib(39) << std::endl;
    TOCK(fib);
    return 0;
}