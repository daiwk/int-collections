/*
 * @lc app=leetcode.cn id=494 lang=cpp
 *
 * [494] 目标和
 */

// @lc code=start
class Solution {
public:
    int cnt = 0;

    void back_track(vector<int>& nums, int target, int idx, int cur_sum) {
        if (idx == nums.size()) {
            if (cur_sum == target) {
                cnt++;
            }
        } else {
            // +
            back_track(nums, target, idx + 1, cur_sum + nums[idx]);
            // -
            back_track(nums, target, idx + 1, cur_sum - nums[idx]);
        }
    }    

    int findTargetSumWays(vector<int>& nums, int target) {
        back_track(nums, target, 0, 0);
        return cnt;
    }
};
// @lc code=end

