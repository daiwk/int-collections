/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */

// @lc code=start
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) {
            return 0;
        }
        vector<int> left_max(n, 0), right_max(n, 0);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                left_max[i] = max(height[i], left_max[i - 1]); // 注意，这里是left_max[i-1]
            } else {
                left_max[i] = height[i];
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            if (i < n - 1) {
                right_max[i] = max(height[i], right_max[i + 1]);// 注意，这里是right_max[i+1]
            } else {
                right_max[i] = height[i];
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += min(left_max[i], right_max[i]) - height[i];
        }
        return res;
    }
};
// @lc code=end

