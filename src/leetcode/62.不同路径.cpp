/*
 * @lc app=leetcode.cn id=62 lang=cpp
 *
 * [62] 不同路径
 */

// @lc code=start
class Solution {
public:
    int uniquePaths(int m, int n) {
        // f(i,j)表示从左上角走到(i,j)的路径数量，
        // 这个点只可能是从左边或者上面走过来的，所以
        // f(i,j) = f(i-1,j) + f(i, j-1)
        // 对于第0行和第0列，f(i,0)=1，f(0,j)=1，因为只有直着能走到
        // f(0,0) = 1
        vector<vector<int> > f(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            f[i][0] = 1;
        }
        for (int j = 0; j < n; ++j) {
            f[0][j] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j <n; ++j) {
                f[i][j] = f[i - 1][j] + f[i][j - 1];
            }
        }
        return f[m - 1][n - 1];
    }
};
// @lc code=end

