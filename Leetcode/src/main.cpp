#include <iostream>
#include "main.h"


int main(int argc, char **argv) {
    q1::Solution1 q1;
    std::vector<int> nums = {1, 2, 3, 4, 5};
    auto res = q1.twoSum(nums, 3);
    for (const auto &item: res) {
        std::cout << item << std::endl;
    }
    return 0;
}
