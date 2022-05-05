#include <iostream>
#include "lc.h"

int main() {
    q1::Solution s;
    std::vector<int> v = {2, 7, 11, 15};
    auto res = s.twoSum(v, 9);

    for (const auto &item: res) {
        std::cout << item << std::endl;
    }

    return 0;
}