/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 */

// @lc code=start
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        vector<vector<int> > D(n+1, vector<int>(m+1));
        for (int i = 0; i < n + 1; ++i) {
            D[i][0] = i;
        }
        for (int j = 0; j < m + 1; ++j) {
            D[0][j] = j;
        }
        for (int i = 1; i < n + 1; ++i) {
            for (int j = 1; j < m + 1; ++j) {
                int a = D[i][j - 1] + 1;
                int b = D[i - 1][j] + 1;
                int c = D[i - 1][j - 1];
                if (word1[i - 1] != word2[j - 1]) { // 注意这里要-1
                    c += 1;
                }
                D[i][j] = min(a, min(b, c));
            }
        }
        return D[n][m];
    }
};
// @lc code=end

