#pragma once
#include <string>

class Solution {
public:
	std::string longestPalindrome(std::string s) {
		std::string res;
		for (int i = 0; i < s.size(); ++i)
		{
			// 以s[i]为中心的最长回文字串
			std::string s1 = palindrome(s, i, i);
			std::string s2 = palindrome(s, i, i + 1);

			res = res.size() > s1.size() ? res : s1;
			res = res.size() > s2.size() ? res : s2;
		}

		return res;
	}

	std::string palindrome(const std::string& s, int l, int r)
	{
		// 防止索引越界
		while (l >= 0 && r < s.size() && s[l] == s[r])
		{
			l--;
			r++;
		}

		// 返回以s[l]和s[r]为中心的最长回文字串
		return s.substr(l + 1, l > 0 ? r - l : r - l - 1);
	}
};
