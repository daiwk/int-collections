/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_res = 0;
        int i = 0, j = height.size() - 1;
        while (i < j) {
            int cur_water = min(height[i], height[j]) * (j - i);
            max_res = max(max_res, cur_water);
            if (height[i] >= height[j]) {
                --j;
            } else {
                ++i;
            }
        }
        return max_res;
    }
};
// @lc code=end

