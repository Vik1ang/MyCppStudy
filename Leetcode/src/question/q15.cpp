#include <algorithm>

namespace q15 {
    class Solution1 {
    public:
        std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
            int n = nums.size();
            std::sort(nums.begin(), nums.end());
            std::vector<std::vector<int>> res;

            // 枚举a
            for (int first = 0; first < n; ++first) {
                // 需要和上一次枚举的数不相同
                if (first > 0 && nums[first] == nums[first - 1]) {
                    continue;
                }

                // c对应的指针指向最右
                int third = n - 1;
                int target = -nums[first];
                // 枚举b
                for (int second = first + 1; second < n; ++second) {
                    // 需要和上一次枚举的数不相同
                    if (second > first + 1 && nums[second] == nums[second - 1]) {
                        continue;
                    }

                    // 需要保证b在c的左侧
                    while (second < third && nums[second] + nums[third] > target) {
                        third--;
                    }

                    // 如果指针从何, 随着b的增加也不会又满足a+b+c=0
                    if (second == third) {
                        break;
                    }

                    if (nums[second] + nums[third] == target) {
                        res.push_back({nums[first], nums[second], nums[third]});
                    }
                }
            }

            return res;
        }
    };
}