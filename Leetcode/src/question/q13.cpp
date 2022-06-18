namespace q13 {
    class Solution1 {
    public:
        int romanToInt(std::string s) {
            int res = 0;
            size_t n = s.length();

            for (int i = 0; i < n; ++i) {
                int val = roman_values[s[i]];
                if (i < n - 1 && val < roman_values[s[i + 1]]) {
                    res -= val;
                } else {
                    res += val;
                }
            }

            return res;
        }

    private:
        std::unordered_map<char, int> roman_values = {
                {'I', 1},
                {'V', 5},
                {'X', 10},
                {'L', 50},
                {'C', 100},
                {'D', 500},
                {'M', 1000},
        };
    };
}