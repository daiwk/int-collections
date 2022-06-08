/*
 * @lc app=leetcode.cn id=1822 lang=cpp
 *
 * [1822] 数组元素积的符号
 */

// @lc code=start
class Solution {
public:
    int arraySign(vector<int>& nums) {
        int res = 0;
        for (auto& i: nums) {
            if (i == 0) {
                return 0;
            }
            res = res ^ i;
        }
        return res >= 0? 1: -1;
    }
};
// @lc code=end

