/*
 * @lc app=leetcode.cn id=283 lang=cpp
 *
 * [283] 移动零
 */

// @lc code=start
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int idx_0 = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                nums[idx_0] = nums[i];
                ++idx_0;
            }
        }
        for (int j = idx_0; j < nums.size(); ++j) {
            nums[j] = 0;
        }
    }
};
// @lc code=end

