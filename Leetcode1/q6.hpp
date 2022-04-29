#pragma once
#include <string>
#include <vector>

class Solution {
public:
	std::string convert(std::string s, int numRows) {
		int n = s.length(), r = numRows;
		if (r == 1 || r >= n)
		{
			return s;
		}
		std::vector<std::string> mat(r);
		for (int i = 0,x = 0, t = r * 2 - 2; i < n ;++i)
		{
			mat[x] += s[i];
			i % t < r - 1 ? ++x : --x;
		}

		std::string res;
		for (const auto& row : mat)
		{
			res += row;
		}

		return res;
	}
};
