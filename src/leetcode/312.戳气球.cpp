/*
 * @lc app=leetcode.cn id=312 lang=cpp
 *
 * [312] 戳气球
 */

// @lc code=start
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int> > dp(n + 2, vector<int>(n + 2));
        vector<int> vals(n + 2);
        // =1是因为v[i]*v[k]*v[j]，为了保证边界得到的还是v[k]
        vals[0] = vals[n + 1] = 1; 
        for (int i = 1; i < n + 1; ++i) {
            vals[i] =  nums[i - 1];
        }
        // 如上所述，从下往上，i可以从n也可以n-1开始，从n开始比较好理解
        for (int i = n; i >= 0; --i) {
            // 从左往右，且保证i < j - 1，即j>i+1
            for (int j = i + 2; j <= n + 1; ++j) {
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] = max(vals[i] * vals[k] * vals[j] + dp[i][k] + dp[k][j], dp[i][j]);
                }
            }
        }
        return dp[0][n + 1];
    }
};
// @lc code=end

