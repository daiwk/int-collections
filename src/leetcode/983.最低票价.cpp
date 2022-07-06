/*
 * @lc app=leetcode.cn id=983 lang=cpp
 *
 * [983] 最低票价
 */

// @lc code=start
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int last = days[days.size() - 1];
        vector<int> dp(last + 1, 0);
        int idx = 0;
        for (int i  = 1; i < last + 1; ++i) {
            if (i == days[idx]) {

                int cost = INT_MAX;
                // 这天要出行
                cost = min(dp[i - 1] + costs[0], cost);
                int seven_days_ago = i > 7? i - 7: 0; // else是0，而不是i!!!
                int thirty_days_ago = i > 30? i - 30: 0; // else是0，而不是i!!!
                cost = min(dp[seven_days_ago] + costs[1], cost);
                cost = min(dp[thirty_days_ago] + costs[2], cost);
                dp[i] = cost;
                ++idx;
            } else {
                dp[i] = dp[i - 1];
            }
        }
        return dp[last];
    }
};
// @lc code=end

