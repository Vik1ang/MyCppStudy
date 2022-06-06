namespace q5 {
    class Solution1 {
    public:
        std::string longestPalindrome(std::string s) {
            std::string res;
            for (int i = 0; i < s.length(); ++i) {
                // 以s[i]为中心
                std::string s1 = palindrome(s, i, i);
                std::string s2 = palindrome(s, i, i + 1);

                res = res.size() > s1.size() ? res : s1;
                res = res.size() > s2.size() ? res : s2;
            }

            return res;
        }

    private:
        std::string palindrome(const std::string& s, int l, int r) {
            while (l >= 0 && r < s.size() && s[l] == s[r]) {
                l--;
                r++;
            }
            return s.substr(l + 1, r - l - 1);
        }
    };
}