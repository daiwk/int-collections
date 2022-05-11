/*
 * @lc app=leetcode.cn id=45 lang=cpp
 *
 * [45] 跳跃游戏 II
 */

// @lc code=start
class Solution {
public:
    int jump(vector<int>& nums) 
    {
        // 目前能跳到的最远位置，要么是i+nums[i]，要么是原来的max_far
        // max_far > i+nums[i]的情况就是比如i=3，nums[3]=1，但原来可以跳到10。
        int max_far = 0;
        int step = 0;   // 跳跃次数
        // 上次跳跃可达范围右边界（下次的最右起跳点）
        int end = 0; 
        for (int i = 0; i < nums.size() - 1; ++i) {
            max_far = max(max_far, i + nums[i]);
            if (end == i) { // 到了这个点，开始跳一步
                end = max_far; // 更新end为下一个最远的地方
                ++step;
            }
        }
        return step;
    }
};
// @lc code=end

