/*
 * @lc app=leetcode.cn id=139 lang=cpp
 *
 * [139] 单词拆分
 */

// @lc code=start
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> xset;
        for (const auto& i: wordDict) {
            xset.emplace(i);
        }
        vector<bool> dp(s.length() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.length(); ++i) {
            for (int j = 0; j < i; ++j) {
                //cout << i << j << s.substr(j, i) << endl;
                bool exists = (xset.find(s.substr(j, i - j)) != xset.end());
                if (exists && dp[j]) {
                    dp[i] = true;
                    //cout << "qqq" << i << j << s.substr(j, i - j) << dp[j] << endl;
                    // 不break也可以，但会有一坨重复计算
                    break;
                }
            }
        }
        return dp[s.length()];
    }
};
// @lc code=end

