namespace q17 {
    class Solution1 {
    public:
        std::vector<std::string> letterCombinations(std::string digits) {
            std::vector<std::string> combination_vector;
            if (digits.empty()) {
                return combination_vector;
            }
            std::unordered_map<char, std::string> phone_map{
                    {'2', "abc"},
                    {'3', "def"},
                    {'4', "ghi"},
                    {'5', "jkl"},
                    {'6', "mno"},
                    {'7', "pqrs"},
                    {'8', "tuv"},
                    {'9', "wxyz"}
            };
            std::string combination;
            back_track(combination_vector, phone_map, digits, 0, combination);
            return combination_vector;
        };
    public:
        void back_track(
                std::vector<std::string> &combination_vector,
                const std::unordered_map<char, std::string> &phone_map,
                const std::string &digits,
                int index,
                std::string &combination) {
            if (index == digits.length()) {
                combination_vector.push_back(combination);
            } else {
                char digit = digits[index];
                const std::string &letters = phone_map.at(digit);
                for (const char &letter: letters) {
                    combination.push_back(letter);
                    back_track(combination_vector, phone_map, digits, index + 1, combination);
                    combination.pop_back();
                }
            }
        }
    };
}