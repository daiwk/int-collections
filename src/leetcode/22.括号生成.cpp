/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */

// @lc code=start
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string cur;
        backtrace(res, cur, 0, 0, n);
        return res;
    }
    // open左括号个数，close 右括号个数
    void backtrace(vector<string>& res, string& cur, int open, int close, int n) {
        if (cur.size() == n * 2) { // 一共2n个左右括号
            res.push_back(cur);
            return; // 终止条件，需要return
        }
        if (open < n) { // 还可以继续加左括号（最多可以加n个）
            cur.push_back('(');
            backtrace(res, cur, open + 1, close, n);
            cur.pop_back();
        }
        if (close < open) { // 准备加新的右括号了
            cur.push_back(')');
            backtrace(res, cur, open, close + 1, n);
            cur.pop_back();
        }
    }
};
// @lc code=end

