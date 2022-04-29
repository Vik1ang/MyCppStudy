#include <unordered_map>
#include <string>

namespace q3 {
    class Solution1 {
    public:
        int lengthOfLongestSubstring(std::string s) {
            int left = 0;
            int right = 0;
            std::unordered_map<char, int> window;
            int length = 0;

            while (right < s.size()) {
                char c = s.at(right);
                window[c]++;

                while (window.at(c) == 2) {
                    char d = s.at(left);
                    window[d]--;
                    left++;
                }

                length = std::max(length, right - left + 1);
                right++;
            }

            return length;
        }
    };
}