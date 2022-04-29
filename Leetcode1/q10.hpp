#pragma once
#include <string>
#include <vector>

class Solution {
public:
	bool isMatch(std::string s, std::string p) {
		const int m = s.size();
		const int n = p.size();

		auto matches = [&](const int i, const int j)
		{
			if (i == 0)
			{
				return false;
			}
			if (p[j - 1] == '.')
			{
				return true;
			}
			return s[i - 1] == p[j - 1];
		};

		std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
		dp[0][0] = true;
		for (int i = 0; i <= m; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				if (p[j - 1] == '*')
				{
					dp[i][j] |= dp[i][j - 2];
					if (matches(i, j - 1))
					{
						dp[i][j] |= dp[i - 1][j];
					}
				}
				else
				{
					if (matches(i, j))
					{
						dp[i][j] = dp[i - 1][j - 1];
					}
				}
			}
		}

		return dp[m][n];
	}
};