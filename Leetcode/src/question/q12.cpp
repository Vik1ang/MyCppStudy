namespace q12 {
    // 对于罗马数字从左到右的每一位，选择尽可能大的符号值
    // 对于 140140 最大可以选择的符号值为 C=100
    // 接下来, 对于剩余的数字 40
    // 最大可以选择的符号值为 XL=40
    // 140 的对应的罗马数字为 C+XL=CXL
    class Solution1 {
    public:
        std::string intToRoman(int num) {
            std::string roman;
            for (const auto &[value, symbol]: roman_value) {
                while (num >= value) {
                    num -= value;
                    roman += symbol;
                }
                if (num == 0) {
                    break;
                }
            }
            return roman;
        }

    public:
        const std::pair<int, std::string> roman_value[13] = {
                {1000, "M"},
                {900,  "CM"},
                {500,  "D"},
                {400,  "CD"},
                {100,  "C"},
                {90,   "XC"},
                {50,   "L"},
                {40,   "XL"},
                {10,   "X"},
                {9,    "IX"},
                {5,    "V"},
                {4,    "IV"},
                {1,    "I"},
        };
    };
}