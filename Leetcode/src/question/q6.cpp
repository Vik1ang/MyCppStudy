#include <string>
#include <vector>

namespace q6 {
    class Solution1 {
    public:
        std::string convert(std::string s, int numRows) {
            int n = s.length(), r = numRows;
            if (r == 1 || r >= n) return s;

            int t = r * 2 - 2;
            std::string ans;
            for (int i = 0; i < r; ++i) { // 枚举矩阵的行
                for (int j = 0; j + i < n; j += t) { // 枚举每个周期的起始下标
                    ans += s[j + i]; // 当前的第一个字符
                    if (i > 0 && i < r - 1 && j + t - i < n) {
                        ans += s[j + t - i]; // 当前的第二个字符
                    }
                }
            }
            return ans;
        }
    };

    class Solution2 {
    public:
        std::string convert(std::string s, int numRows) {
            if (numRows == 1) return s;

            std::vector<std::string> rows(std::min(numRows, int(s.size()))); // 防止s的长度小于行数
            int curr_row = 0;
            bool going_down = false;

            for (char c: s) {
                rows[curr_row] += c;
                if (curr_row == 0 || curr_row == numRows - 1) { // 当前行curRow为0或numRows -1时，箭头发生反向转折
                    going_down = !going_down;
                }
                curr_row += going_down ? 1 : -1;
            }

            std::string ret;
            for (const auto &row: rows) {
                ret += row;
            }

            return ret;
        }
    };

    class Solution3 {
    public:
        std::string convert(std::string s, int numRows) {
            if (numRows == 1) return s;

            int step = numRows * 2 - 2; // 间距
            int index = 0; // s的下标
            int len = s.length();
            int add = 0; // 真实的间距
            std::string ret;

            for (int i = 0; i < numRows; ++i) {
                index = i;
                add = i * 2;
                while (index < len) { // 超出字符串长度计算下一层
                    ret += s[index];
                    add = step - add; // 第一次间距是 step - 2 * i, 第二次是2 * i
                    index += (i == 0 || i == numRows - 1) ? step : add; // 0行和最后一行使用step间距，其余使用add间距
                }
            }

            return ret;
        }
    };
}