/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */

// @lc code=start
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, max_res = nums[0];
        for (int i = 0; i < nums.size(); ++i) {
            pre = max(pre + nums[i], nums[i]);
            max_res = max(max_res, pre);
        }
        return max_res;
    }
};
// @lc code=end

