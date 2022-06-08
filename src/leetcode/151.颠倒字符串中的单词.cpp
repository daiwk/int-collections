/*
 * @lc app=leetcode.cn id=151 lang=cpp
 *
 * [151] 颠倒字符串中的单词
 */

// @lc code=start
class Solution {
public:
    string reverseWords(string s) {
        int left = 0;
        int right = s.size() - 1;
        while (left < s.size() && s[left] == ' ') {
            ++left;
        }
        while (right >= 0 && s[right] == ' ') {
            --right;
        }
        deque<string> q;
        string word = "";
        while (left <= right) {
            if (s[left] == ' ' && word != "") {
                // cout << word << " " << left << " " << right << endl;
                q.push_front(word);
                word = "";
            } else {
                if (s[left] != ' ') {
                    word += s[left];
                }
            }
            left++;
        }
        q.push_front(word);
        string res;
        while (!q.empty()) {
            res += q.front();
            q.pop_front();
            if (!q.empty()) {
                res += " ";
            }
        }
        return res;
    }
};
// @lc code=end

