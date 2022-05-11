/*
 * @lc app=leetcode.cn id=14 lang=cpp
 *
 * [14] 最长公共前缀
 */

// @lc code=start
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string comm_prefix = strs[0];
        for (int i = 0; i < strs.size(); ++i) {
            lcp_sub(strs[i], comm_prefix);
            if (comm_prefix == "") {
                return comm_prefix;
            }
        }
        return comm_prefix;
    }
    void lcp_sub(const string &a, string& b) {
        int len = min(a.length(), b.length());
        int i = 0;
        // while一起判断了，就不用再对i i+1处理了。。
        while (i < len && a[i] == b[i]) {
            ++i;
        }
        b = b.substr(0, i);
    }
};
// @lc code=end

