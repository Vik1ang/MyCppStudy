#include <algorithm>

namespace q16 {
    class Solution1 {
    public:
        int threeSumClosest(std::vector<int>& nums, int target) {
            int n = nums.size();
            int best = 1e7;
            std::sort(nums.begin(), nums.end());

            // 根据差值的绝对值来更新答案
            auto update = [&](int curr) {
                if (std::abs(curr - target) < std::abs(best - target)) {
                    best = curr;
                }
            };

            // 枚举a
            for (int i = 0; i < n; ++i) {
                // 保证和上一次的值不相等
                if (i > 0 && nums[i] == nums[i - 1]) {
                    continue;
                }

                // 使用双指针枚举b和c
                int j = i + 1, k = n - 1;
                while (j < k) {
                    int sum = nums[i] + nums[j] + nums[k];
                    // 如果和为target, 直接返回
                    if (sum == target) {
                        return target;
                    }

                    update(sum);
                    if (sum > target) {
                        // 如果和大于target, 移动c
                        int k0 = k - 1;
                        while (j < k0 && nums[k0] == nums[k]) {
                            k0--;
                        }
                        k = k0;
                    } else {
                        // 如果和小于target, 移动b
                        int j0 = j + 1;
                        while (j0 < k && nums[j0] == nums[j]) {
                            j0++;
                        }
                        j = j0;
                    }
                }
            }
            return best;
        }
    };
}