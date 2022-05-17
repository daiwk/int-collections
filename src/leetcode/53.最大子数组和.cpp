/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */

// @lc code=start
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // f(i)表示以第i个数结尾的连续子数组最大和，那么求的就是i=0,...,n-1的max f(i)
        // f(i) = max(f(i-1) + nums[i], nums[i])
        // 如果加上这个数能变得更大，那就加上；如果不行，那这个数就是新的起点
        int pre = 0;
        int max_res = INT_MIN; // 初始化极小值，或者nums[0]
        for (int i = 0; i < nums.size(); ++i) {
            pre = max(pre + nums[i], nums[i]);
            max_res = max(max_res, pre);
        }
        return max_res;
    }
};
// @lc code=end

