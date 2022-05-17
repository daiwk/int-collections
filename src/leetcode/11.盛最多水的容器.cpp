/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        // 对于i，j两个点，能接的水量是min(num[i],num[j]) * (j - i)
        // 这个时候应该移动的是num[i]和num[j]中较小的那个，因为j-i肯定会变小，
        // 而想要变大，只能min(num[i],num[j])变大，所以要把小的移一下试试，如果小的在左边那就右移，否则同理
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

