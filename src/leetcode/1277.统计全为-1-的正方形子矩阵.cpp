/*
 * @lc app=leetcode.cn id=1277 lang=cpp
 *
 * [1277] 统计全为 1 的正方形子矩阵
 */

// @lc code=start
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();// row
        if (m < 1) return 0;
        int n = matrix[0].size(); // col
        int maxnum = 0;

        vector<vector<int> > dp(m, vector<int>(n));
        
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 1) {
                dp[i][0] = 1;
                maxnum += 1;
            }
        }
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 1) {
                dp[0][j] = 1;
                // 如果不判断，dp[0][0]就算了两次。。
                if (j != 0) {
                    maxnum += 1;
                }
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 1) {
                    dp[i][j] = min(min(dp[i - 1][j], dp[i - 1][j - 1]), dp[i][j - 1]) + 1; 
                }
                //cout << dp[i][j] << " " << i << " " << j << endl;
                maxnum += dp[i][j];
            }
        }
        return maxnum;
    }
};
// @lc code=end

