/*
 * @lc app=leetcode.cn id=581 lang=cpp
 *
 * [581] 最短无序连续子数组
 */

// @lc code=start
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int len = nums.size();
        // 右往左的最小值
        int min_n = nums[len - 1];
        // 左往右的最大值
        int max_n = nums[0];
        // right=-1，因为有可能本身数组有序
        int left = 0, right = -1;
        for (int i = 0; i < len; ++i) {
            if (nums[i] >= max_n) {
                max_n = nums[i];
            } else {
                // nums[i]比左到右的最大值要小，记录一下
                // 因为会一直往右走，所以最后的就是最右的
                right = i;
            }

            if (nums[len - 1 - i] <= min_n) {
                min_n = nums[len - 1 - i];
            } else {
                // 同理
                left = len - i - 1;
            }
        }
        return right == -1? 0: right - left + 1;
    }
};
// @lc code=end

