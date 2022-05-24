/*
 * @lc app=leetcode.cn id=647 lang=cpp
 *
 * [647] 回文子串
 */

// @lc code=start
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size(), res = 0;
        for (int i = 0; i < 2 * n - 1; ++i) {
            int l = i / 2, r = l + i % 2;
            while (l >= 0 && r < n && s[l] == s[r]) {
                --l;
                ++r;
                ++res;
            }
        }
        return res;
    }
};
// @lc code=end

