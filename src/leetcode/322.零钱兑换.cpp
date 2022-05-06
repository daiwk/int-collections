/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 */

// @lc code=start
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp[i]：组成金额i需要的最少硬币数
        // dp[i] = min(dp[i-c[j]) + 1, j = 0,...,n-1，
        // ！！！注意，是两项,dp[i]和dp[i - coins[j]]+ 1
        // dp[i] = min(dp[i], dp[i - coins[j]]+ 1);
        // c[j]是第j个面额，+1表示选择这个面额，那i-c[j]就是剩下的面额了
        // ！！需要判断凑不出的情况：把dp初始化为amount + 1，如果凑不出就不更新，
        // 如果最后还是amount +1那就是凑不出，当然也可以是amount+999
        int xmax = amount + 1;
        // 因为最后一个下标要是amount，所以大小是amount + 1
        vector<int> dp(amount + 1, xmax);
        dp[0] = 0;
        for(int i = 1; i <= amount; ++i) {
            for (int j = 0; j < coins.size(); ++j) {
                // 遍历每种面额
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]]+ 1);
                }
            }
        }
        return dp[amount] > amount? -1: dp[amount];
    }
};
// @lc code=end

