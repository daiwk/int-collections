/*
 * @lc app=leetcode.cn id=6 lang=cpp
 *
 * [6] Z 字形变换
 */

// @lc code=start
class Solution {
public:
    string convert(string s, int numRows) {
        int t = 2 * numRows - 2;
        int i = 0;
        if (t == 0) {
            return s;
        }
        int round = s.length() / t;
        string res;
        while (i < numRows) {
            for (int j = 0; j + i < s.length(); j += t) {
                // 循环k轮，枚举每轮的起始下标
                res.push_back(s[j + i]); // 当前周期第一个字符
                // 注意，这里要限制0<i < numRows -1，因为第一行和最后一行只加一个数！！！！！
                if (0 < i && i < numRows - 1 && j + t - i < s.length()) {
                    res.push_back(s[j + t - i]);
                }
            }
            ++i;
        }
        return res;
    }
};
// @lc code=end

