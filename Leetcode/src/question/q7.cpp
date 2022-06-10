namespace q7 {
    class Solution1 {
    public:
        int reverse(int x) {
            int res = 0;

            while (x != 0) {
                // 取末尾的数字
                int tmp = x % 10;
                // 判断是否超出范围
                if (res > INT_MAX / 10 || (res == INT_MAX && tmp > 7)) {
                    return 0;
                }
                // 判断是否小于范围
                if (res < INT_MIN / 10 || (res == INT_MIN && tmp < -8)) {
                    return 0;
                }
                res = res * 10 + tmp;
                x /= 10;
            }
            return res;
        }
    };
}