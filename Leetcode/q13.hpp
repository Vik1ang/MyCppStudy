#pragma once
#include <string>
#include <unordered_map>

class Solution
{
private:
	std::unordered_map<char, int> symbol_values = {
		{'I', 1},
		{'V', 5},
		{'X', 10},
		{'L', 50},
		{'C', 100},
		{'D', 500},
		{'M', 1000},
	};

public:
	int romanToInt(std::string s) {
		int ans = 0;
		const int n = s.length();
		for (int i = 0; i < n; ++i)
		{
			const int value = symbol_values[s[i]];
			if (i < n - 1 && value < symbol_values[s[i + 1]])
			{
				ans -= value;
			}
			else
			{
				ans += value;
			}
		}
		return ans;
	}
};
