namespace q9 {
    class Solution1 {
    public:
        bool isPalindrome(int x) {
            if (x < 0 || (x % 10 == 0 && x != 0)) {
                return false;
            }

            int reverted_num = 0;
            while (x > reverted_num) {
                reverted_num = reverted_num * 10 + x % 10;
                x /= 10;
            }

            return x == reverted_num || x == reverted_num / 10;
        }
    };
}