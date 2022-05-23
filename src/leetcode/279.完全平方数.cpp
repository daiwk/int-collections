/*
 * @lc app=leetcode.cn id=279 lang=cpp
 *
 * [279] 完全平方数
 */

// @lc code=start
class Solution {
public:
    int numSquares(int n) {
        vector<int> f(n + 1);
        // 边界，f[0]= 0
        for (int i = 1; i <= n; ++i) {
            int res = INT_MAX;
            for (int j = 1; j * j <= i; ++j) {
                res = min(res, f[i - j * j]);
            }
            f[i] = res + 1;
        }
        return f[n];
    }
};
// @lc code=end

