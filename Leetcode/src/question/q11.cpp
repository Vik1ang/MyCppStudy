namespace q11 {
    class Solution1 {
    public:
        int maxArea(std::vector<int> &height) {
            int left = 0, right = height.size() - 1;
            int res = 0;
            while (left < right) {
                int area = std::min(height[left], height[right]) * (right - left);
                res = std::max(area, res);
                if (height[left] < height[right]) {
                    left++;
                } else {
                    right--;
                }
            }

            return res;
        }
    };
}