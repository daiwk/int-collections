/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 */

// @lc code=start
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> dp;
        dp.reserve(nums.size());
        if (nums.empty()) {
            return 0;
        }
        dp[0] = nums[0];
        if (nums.size() == 1) {
            return dp[0];
        }
        dp[1] = max(nums[0], nums[1]);
        if (nums.size() == 2) {
            return dp[1];
        }
        for (int i = 2; i < nums.size(); ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[nums.size() - 1];
    }
};
// @lc code=end

