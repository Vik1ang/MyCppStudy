#include "Leetcode.h"

int main()
{
	std::vector<int> nums = { 2,7,11,15 };
	std::vector<int> rtn = Solution().twoSum(nums, 9);
	for (int value : rtn)
	{
		std::cout << value << std::endl;
	}

	return EXIT_SUCCESS;
}