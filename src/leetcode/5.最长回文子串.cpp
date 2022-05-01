/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 */

// @lc code=start
class Solution {
public:
    string longestPalindrome(string s) {
        // p(i,j)表示i:j是回文串
        // 转移：
        // if  si == sj then p(i,j) = p(i+i, j-1)
        // 边界：len=1是，len=2，如果si==sj那是
        // 结果就是所有p(i,j)=1的j-i+1的max
        int n = s.size();
        if (n < 2) {
            return s;
        }
        int max_len = 1;
        int begin = 0;
        // n * n的矩阵
        vector<vector<bool> > dp(n, vector<bool>(n));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;//1个字符的肯定是

        }
        // L是子串长度
        for (int L = 2; L <= n; ++L) {
            for (int i = 0; i < n; ++i) {
                // 根据L找j的位置, L = j-i+1
                int j = L + i - 1;
                if (j >= n) {
                    break; // 到尽头了
                }
                if (s[i] != s[j]) {
                    dp[i][j] = false;
                } else {
                    if (j - i < 3) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }

                if (dp[i][j] && L > max_len) {
                    max_len = L;
                    begin = i;
                }

            }
        }
        return s.substr(begin, max_len);

    }
};
// @lc code=end

