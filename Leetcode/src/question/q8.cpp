namespace q8 {
    class Solution1 {
    public:
        int myAtoi(std::string s) {
            int n = s.size();
            int index = 0;
            int res = 0;

            // 跳过空格
            while (index < n && s.at(index) == ' ') {
                index++;
            }
            // 如果字符串全是空格直接返回
            if (index == n) {
                return 0;
            }

            // 判断正负
            bool is_negative = false;
            if (s.at(index) == '-') {
                is_negative = true;
            }

            // 如果是正负号把索引向后移动一次
            if (s.at(index) == '-' || s.at(index) == '+') {
                index++;
            }

            // 循环判断字符是否在 0~9之间
            while (index < n && s.at(index) >= '0' && s.at(index) <= '9') {
                int temp = s.at(index) - '0';

                if (!is_negative && (res > INT_MAX / 10 || (res == (INT_MAX / 10) && temp >= 7))) {
                    return INT_MAX;
                }
                if (is_negative && (-res < INT_MIN / 10 || (-res == (INT_MIN / 10) && temp >= 8))) {
                    return INT_MIN;
                }
                res = res * 10 + temp;
                index++;
            }

            // 如果是负数
            if (is_negative) return -res;

            return res;
        }
    };
}