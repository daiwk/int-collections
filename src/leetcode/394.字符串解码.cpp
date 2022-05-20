/*
 * @lc app=leetcode.cn id=394 lang=cpp
 *
 * [394] 字符串解码
 */

// @lc code=start
class Solution {
public:
    string get_string(const vector<string>& vec) {
        string tmp_str = "";
        for (int j = 0; j < vec.size(); ++j) {
            tmp_str += vec[j];
        }
        return tmp_str;
    }

    string decodeString(string s) {
        stack<string> stk;
        size_t ptr = 0;
        string res = "";
        while (ptr < s.size()) {
            if (isdigit(s[ptr])) {
                string tmp_str = "";
                while (isdigit(s[ptr])) {;
                    tmp_str += string(1, s[ptr++]);
                }
                stk.push(tmp_str);
            } else if (isalpha(s[ptr]) || s[ptr] == '[') {
                stk.push(string(1, s[ptr++]));
            } else if (s[ptr] == ']') {
                vector<string> tmp_vec;
                vector<string> tmp_str_vec;
                while(stk.top() != "[") {
                    string tmp = stk.top();
                    tmp_str_vec.push_back(tmp);
                    stk.pop();
                }
                reverse(tmp_str_vec.begin(), tmp_str_vec.end());
                string tmp_str = get_string(tmp_str_vec);
                cout << tmp_str << endl;
                stk.pop(); // pop掉[
                int digit = atoi(stk.top().c_str()); // atoi转成int
                stk.pop();
                string x_str = "";
                while (digit) {
                    tmp_vec.push_back(tmp_str);
                    digit--;
                }
                string xtmp_str = get_string(tmp_vec);
                stk.push(xtmp_str);// 要塞回栈里去！！！
                cout << xtmp_str << "qqq" << endl;
                ptr++;
            }
        }
        vector<string> res_vec;
        // 全部搞出来，因为可能会有多段结果
        while(!stk.empty()) {
            res_vec.push_back(stk.top());
            stk.pop();
        }
        reverse(res_vec.begin(), res_vec.end());
        res = get_string(res_vec);
        return res;
    }
};
// @lc code=end

