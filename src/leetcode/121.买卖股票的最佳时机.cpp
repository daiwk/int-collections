/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minprice = INT_MAX;
        int max_profit = 0;
        for (int i = 0; i < prices.size(); ++i) {
            if (prices[i] < minprice) {
                // 不卖
                minprice = prices[i];
            } else {
                // 卖或者不卖的最大profit
                max_profit = max(max_profit, prices[i] - minprice);
            }
        }
        return max_profit;
    }
};
// @lc code=end

