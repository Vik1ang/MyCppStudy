namespace q14 {
    class Solution1 {
    public:
        std::string longestCommonPrefix(std::vector<std::string> &strs) {
            std::string res;
            if (strs.empty()) {
                return res;
            }

            res = strs[0];
            for (int i = 1; i < strs.size(); ++i) {
                int j = 0;
                for (; j < strs[i].size(); ++j) {
                    if (res[j] != strs[i][j]) {
                        break;
                    }
                }
                res = res.substr(0, j);
                if (res.empty()) return res;
            }

            return res;
        }
    };
}