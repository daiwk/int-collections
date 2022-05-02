/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 */

// @lc code=start
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        // 回溯+dfs
        unordered_map<char, string> phone_map {
            {'2', "abc"}, 
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
        };
        vector<string> res;
        if (digits.empty()) {
            return res;
        }
        string comb;
        backtrace(res, phone_map, digits, 0, comb);
        return res;
    }
    void backtrace(vector<string>& res, const unordered_map<char, string>& phone_map, 
        const string& digits, int index, string& comb_str) {
            // index:输入的digits的第index个字母
            if (index == digits.length()) {
                 res.push_back(comb_str);
            } else {
                char digit = digits[index];
                const string& letters = phone_map.at(digit);
                for (const char& letter: letters) {
                    comb_str.push_back(letter); // 先搞一个
                    backtrace(res, phone_map, digits, index + 1, comb_str);
                    comb_str.pop_back(); // 扔掉，换一个新的
                }
            }

    }
};
// @lc code=end

