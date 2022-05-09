/*
 * @lc app=leetcode.cn id=221 lang=cpp
 *
 * [221] 最大正方形
 */

// @lc code=start
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();// row
        if (m < 1) return 0;
        int n = matrix[0].size(); // col
        int maxnum = 0;

        vector<vector<int> > dp(m, vector<int>(n));
        
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == '1') {
                dp[i][0] = 1;
                maxnum = 1;
            }
        }
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == '1') {
                dp[0][j] = 1;
                maxnum = 1;
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    dp[i][j] = min(min(dp[i - 1][j], dp[i - 1][j - 1]), dp[i][j - 1]) + 1;
                    maxnum = max(maxnum, dp[i][j]);
                }
            }
        }
        return maxnum * maxnum;
    }
};
// @lc code=end

