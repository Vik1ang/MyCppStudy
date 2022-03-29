#pragma once
#include <string>

class Solution {
public:
	int myAtoi(std::string s) {
		const size_t length = s.length();

		// 去除空格
		size_t index = 0;
		while (index < length)
		{
			if (s[index] != ' ')
			{
				break;
			}
			index++;
		}

		if (index == length)
		{
			return 0;
		}

		int sign = 1;
		// 处理第1个非空字符为正负符号，这两个判断需要写在一起
		if (s[index] == '+')
		{
			index++;
		}
		else if (s[index] == '-')
		{
			sign = -1;
			index++;
		}

		// 根据题目限制，只能使用int
		int res = 0;
		while (index < length)
		{
			const char currChar = s[index];
			if (currChar < '0' || currChar > '9')
			{
				break;
			}

			if (res > INT_MAX / 10 || (res == INT_MAX / 10 && (currChar - '0') > INT_MAX % 10))
			{
				return INT_MAX;
			}
			if (res < INT_MIN / 10 || (res == INT_MIN / 10 && (currChar - '0') > -(INT_MIN % 10)))
			{
				return INT_MIN;
			}

			res = res * 10 + sign * (currChar - '0');
			index++;
		}

		return res;
	}
};