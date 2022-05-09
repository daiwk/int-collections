/*
 * @lc app=leetcode.cn id=152 lang=cpp
 *
 * [152] 乘积最大子数组
 */

// @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int min_f = nums[0], max_f = nums[0];
        int res = nums[0];
        for (int i = 1; i < n; ++i) {
            int cur = nums[i];
            int mx = max_f, mn = min_f; //必须搞个临时变量，因为改完max_f后，算min_f的时候还要用原来的max_f
            max_f = max(max(mn * cur, mx * cur), cur);
            min_f = min(min(mn * cur, mx * cur), cur);
            res = max(res, max_f);
        }
        return res;
    }
};
// @lc code=end

