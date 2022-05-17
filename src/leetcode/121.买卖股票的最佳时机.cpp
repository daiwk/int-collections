/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // 找到最小的谷之后的最大的峰。 我们可以维持两个变量
        // minprice ：迄今为止所得到的最小的谷值。初始化为int_max，如果当前价格比它小，那就更新它为当前价格
        // maxprofit，迄今为止所得到的最大的利润（卖出价格与最低价格之间的最大差值）。如果当前价格与minprice的差比它大，那就更新它
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

