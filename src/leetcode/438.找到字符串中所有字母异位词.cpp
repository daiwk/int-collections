/*
 * @lc app=leetcode.cn id=438 lang=cpp
 *
 * [438] 找到字符串中所有字母异位词
 */

// @lc code=start
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> need, window;
        // 目标map
        for (char c: p) {
            need[c]++;
        }
        int left = 0, right = 0;
        int valid = 0;
        vector<int> res;
        while (right < s.size()) {   
            char c = s[right];
            right++;
            if (need.count(c)) {
                // 只有这个字母是需要的，才会放到window这个count里
                window[c]++;
                if (window[c] == need[c]) {
                    // 这个字母的count正确，那就valid++
                    valid++;
                }
            }
            // 判断左窗口是否要收缩
            while (right - left >= p.size()) {
                // right-left可能超过窗口长度，可能需要收缩
                if (valid == need.size()) {
                    // 所有字符均count正确
                    res.push_back(left);
                }
                char d = s[left];
                left++;
                if (need.count(d)) {
                    // 只有这个字母是需要的，才会放到window这个count里
                    if (window[d] == need[d]) {
                        valid--;
                        // 因为这个时候原来的left已经不在窗口里了
                        // 所以要去掉这个合法字符
                    }
                    // 原来的left不在窗口里了，所以窗口记数也要--
                    window[d]--;
                }
            }
        }
        return res;
    }
};
// @lc code=end

