/*
 * @lc app=leetcode.cn id=26 lang=cpp
 *
 * [26] 删除有序数组中的重复项
 */

// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int i = 0;
        for (int j = 1; j < nums.size(); j++) {
            if (nums[j] != nums[i]) {
                // 不相等，且j比i快，那就说明ij中间可能是一串重复的数，
                // 就把num[j]赋值给num[i+1],然后两个指针都往后移
                nums[i + 1] = nums[j];
                ++i;
            }
        }
        return i + 1;
    }
};
// @lc code=end

