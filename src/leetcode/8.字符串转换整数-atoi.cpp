/*
 * @lc app=leetcode.cn id=8 lang=cpp
 *
 * [8] 字符串转换整数 (atoi)
 */

// @lc code=start

class AToI {
    string state = "start";
    unordered_map<string, vector<string> > table = {
        {"start", {"start", "signed", "in_number", "end"}},
        {"signed", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}
    };
    int get_next_stat(char c) {
        if (isspace(c)) { // " "
            return 0;
        }
        if (c == '+' || c == '-') { // +/-
            return 1;
        }
        if (isdigit(c)) { // number
            return 2;
        }
        return 3; // other
    }
public:
    int sign = 1;
    long long res = 0;
    void get(char c) {
        state = table[state][get_next_stat(c)];//获取下一个状态
        if (state == "in_number") {
            res = res * 10 + c - '0';
            // 这个比较重要。。越界的时候取一下long long的max和min
            // 这里其实没用上sign，所以最后要用！！
            res = sign == 1? min(res, (long long)INT_MAX): min(res, -(long long)INT_MIN);
        } else if (state == "signed") {
            sign = c == '+'? 1: -1;
        }
    }
};

class Solution {
public:
    int myAtoi(string s) {
        AToI a;
        for (char c: s) {
            a.get(c);
        }
        return a.sign * a.res;
    }
};
// @lc code=end

