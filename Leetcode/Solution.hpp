#pragma once
#include <string>

const std::pair<int, std::string> value_symbols[] =
{
	{1000, "M"},
	{900, "CM"},
	{500, "D"},
	{400, "CD"},
	{100, "C"},
	{90, "XC"},
	{50, "L"},
	{40, "XL"},
	{10, "X"},
	{9, "IX"},
	{5, "V"},
	{4, "IV"},
	{1, "I"},
};

class Solution {
public:
	std::string intToRoman(int num)
	{
		std::string roman;
		for (auto &[value, symbol] : value_symbols)
		{
			while (num >= value)
			{
				num -= value;
				roman += symbol;
			}
			if (num == 0)
			{
				break;
			}
		}

		return roman;
	}
};