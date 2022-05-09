/*
 * @lc app=leetcode.cn id=10 lang=cpp
 *
 * [10] 正则表达式匹配
 */

// @lc code=start
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        // 因为f是n+1 * m+1，所以这里其实是比较 s[i-1]和p[j-1]
        // [&]：父作用域的按引用传，其实[=]也行，父作用域的按值传
        auto matches = [=](int i, int j) {
            if (i == 0) {
                return false; // 不太懂这个
            }
            if (p[j - 1] == '.') {
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] != '*')  {
                    if (matches(i, j)) { //比较的是i-1和j-1
                        f[i][j] |= f[i - 1][j - 1];
                    }
                } else { 
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1)) { // 比较的是i-1和j-2
                        f[i][j] |= f[i - 1][j];
                    }
                }
            }
        }
        return f[m][n];
    }
};
// @lc code=end

