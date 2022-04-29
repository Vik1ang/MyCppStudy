#pragma once
#include <algorithm>
#include <vector>

class Solution {
public:
	std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
		const int n = nums.size();
		std::sort(nums.begin(), nums.end());
		std::vector<std::vector<int>> ans;

		// 枚举a
		for (int first = 0; first < n; ++first)
		{
			// 枚举不相同
			if (first > 0 && nums[first] == nums[first - 1])
			{
				continue;
			}

			// c指向最右
			int third = n - 1;
			int target = -nums[first];

			// 枚举b
			for (int second = first + 1; second < n; ++second)
			{
				// 要保证不一样
				if (second > first + 1 && nums[second] == nums[second - 1])
				{
					continue;
				}
				// 保证b在c左侧
				while (second < third && nums[second] + nums[third] > target)
				{
					--third;
				}
				// 指针重合
				if (second == third)
				{
					break;
				}
				if (nums[second] + nums[third] == target)
				{
					ans.push_back({nums[first], nums[second], nums[third]});
				}
			}
		}

		return ans;
	}
};
