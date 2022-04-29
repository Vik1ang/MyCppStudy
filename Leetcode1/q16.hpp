#pragma once
#include <algorithm>
#include <vector>

class Solution {
public:
	int threeSumClosest(std::vector<int>& nums, int target) {
		std::sort(nums.begin(), nums.end());
		const int n = nums.size();
		int best = 1e7;

		// 根据差值绝对值来更新答案
		auto  update = [&](const int cur)
		{
			if (std::abs(cur - target) < std::abs(best - target))
			{
				best = cur;
			}
		};

		// 枚举a
		for (int i = 0; i < n; ++i)
		{
			// 保证和上次不一样
			if (i > 0 && nums[i] == nums[i - 1])
			{
				continue;
			}
			// 使用双指针枚举b和c
			int j = i + 1, k = n - 1;
			while (j < k)
			{
				const int sum = nums[i] + nums[j] + nums[k];
				// 如果和为target直接返回答案
				if (sum == target)
				{
					return target;
				}
				update(sum);
				if (sum > target)
				{
					// 如果和大于target, 移动c对应的指针
					int k0 = k - 1;
					while (j < k0 && nums[k0] == nums[k])
					{
						--k0;
					}
					k = k0;
				}
				else
				{
					// 如果和小于target, 移动b对应的指针
					int j0 = j + 1;
					// 移动到下一个不相等的元素
					while (j0 < k && nums[j0] == nums[j])
					{
						++j0;
					}
					j = j0;
				}
			}
		}

		return best;
	}
};