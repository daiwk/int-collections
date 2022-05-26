/*
 * @lc app=leetcode.cn id=301 lang=cpp
 *
 * [301] 删除无效的括号
 */

// @lc code=start
class Solution {
public:

    vector<string> res;
    bool is_valid(const string& str) {
        int cnt = 0;
        for (auto& i: str) {
            if (i == '(') {
                cnt++;
            } else if (i == ')') {
                cnt--;
                // 这个必须要有，不然可能出来)(的情况。。还return了true
                if (cnt < 0) {
                    return false;
                }
            }
        }
        return cnt == 0;
    }

    void backtrace(string ss, int start, int l_remove, int r_remove) {
        if (l_remove == 0 && r_remove == 0) {
            if (is_valid(ss)) {
                res.push_back(ss);
                return;
            }
        }
        // i从start开始
        for (int i = start; i < ss.size(); ++i) {
            // 需要加这个，要不然出来的结果会有重复
            if (i != start && ss[i] == ss[i - 1]) {
                continue;
            }
            if (l_remove + r_remove > ss.size() - i) {
                // 肯定凑不成
                return;
            }
            if (l_remove > 0 && ss[i] == '(') {
                backtrace(ss.substr(0, i) + ss.substr(i + 1), i, l_remove - 1, r_remove);
            }
            if (r_remove > 0 && ss[i] == ')') {
                backtrace(ss.substr(0, i) + ss.substr(i + 1), i, l_remove, r_remove - 1);
            }
        }

    }
    vector<string> removeInvalidParentheses(string s) {
        int l_remove = 0, r_remove = 0;
        for (auto& i: s) {
            if (i == '(') {
                l_remove++;
            } else if (i == ')') {
                if (l_remove == 0) {
                    r_remove++;//多出了一个右括号
                } else {
                    l_remove--;// 能找到匹配的
                }
            }
        }
        backtrace(s, 0, l_remove, r_remove);
        return res;
    }
};
// @lc code=end

