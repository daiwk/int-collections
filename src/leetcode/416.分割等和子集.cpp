/*
 * @lc app=leetcode.cn id=416 lang=cpp
 *
 * [416] 分割等和子集
 */

// @lc code=start
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return false;
        }
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int max_num = *max_element(nums.begin(), nums.end());
        if (sum % 2 == 1) {
            return false;
        }
        int target = sum / 2;
        if (max_num > target) {
            return false;
        }
        vector<vector<int> > dp(n, vector<int>(target + 1, 0));
        for(int i = 0; i < n; ++i) {
            dp[i][0] = true;
        }
        dp[0][nums[0]] = true;
        for (int i = 1; i < n; ++i) {
            int num = nums[i];
            for (int j = 1; j <= target; ++j) {
                if (num > j) {
                    dp[i][j] = dp[i - 1][j];
                } else { // num <= j
                    dp[i][j] = dp[i - 1][j - num] | dp[i - 1][j];
                }
            }
        }
        return dp[n - 1][target];

    }
};
// @lc code=end

