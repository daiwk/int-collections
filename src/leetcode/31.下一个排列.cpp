/*
 * @lc app=leetcode.cn id=31 lang=cpp
 *
 * [31] 下一个排列
 */

// @lc code=start
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;// 因为要和i+1比较
        //找到第一个a[i]<a[i+1]
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            --i;
        }
        if (i >= 0) {
            int j = nums.size() - 1;
            // 找到第一个j，使得a[i]>a[j]
            while (j >= 0 && nums[i] >= nums[j]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }
        // 就算i<0，那就是i=-1，仍然成立
        reverse(nums.begin() + i + 1, nums.end());
    }
};
// @lc code=end

