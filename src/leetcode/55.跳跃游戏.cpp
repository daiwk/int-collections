/*
 * @lc app=leetcode.cn id=55 lang=cpp
 *
 * [55] 跳跃游戏
 */

// @lc code=start
class Solution {
public:
    bool canJump(vector<int>& nums) {
        // 贪心
        // 对于每个位置x，实时维护最远可到达的位置x+nums[x]，
        // 如果这个位置x在最远可到达位置内，那么可以从起点经过若干次跳跃到达
        // 在遍历的过程中，如果最远可到达位置>=数组最后一个位置 ，就可以return True
        int n = nums.size();
        int most_right = 0;
        for (int i = 0; i < n; ++i) {
            if (i <= most_right) {
                most_right = max(most_right, i + nums[i]);
                if (most_right >= n - 1) {
                    return true;
                }
            }
        }
        return false;
    }
};
// @lc code=end

