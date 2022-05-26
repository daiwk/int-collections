/*
 * @lc app=leetcode.cn id=238 lang=cpp
 *
 * [238] 除自身以外数组的乘积
 */

// @lc code=start
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        vector<int> r_product(len, 0);
        vector<int> res(len);
        res[0] = 1;
        for (int i = 1; i < len; ++i) {
            res[i] = nums[i - 1] * res[i - 1];
        }
        int r = 1;
        for (int i = len - 1; i >= 0; --i) {
            res[i] = res[i] * r;
            r *= nums[i];
        }
        return res;
    }
};
// @lc code=end

