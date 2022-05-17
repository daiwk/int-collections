/*
 * @lc app=leetcode.cn id=32 lang=cpp
 *
 * [32] 最长有效括号
 */

// @lc code=start
class Solution {
public:
    int longestValidParentheses(string s) {
        int max_res = 0;
        stack<int> stk;
        stk.push(-1);// 如上所述，为了保证栈底一直是xxx的右括号
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') {
                stk.push(i);
            } else if (s[i] == ')') {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i);
                } else {
                    max_res = max(max_res, i - stk.top());
                }
            }
        }
        return max_res;
    }
};
// @lc code=end

