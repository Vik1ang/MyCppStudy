#include "ticktock.h"
#include <cmath>
#include <iostream>
#include <vector>

int main()
{
    size_t n = 1 << 27;
    std::vector<float> a;

    TICK(filter);
    for (size_t i = 0; i < n; i++) {
        float val = std::sin(i);
        if (val > 0) {
            a.push_back(val);
        }
    }
    TOCK(filter);

    return 0;
}