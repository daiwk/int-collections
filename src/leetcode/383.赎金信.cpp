/*
 * @lc app=leetcode.cn id=383 lang=cpp
 *
 * [383] 赎金信
 */

// @lc code=start
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> cnt(26);
        for (char& i: magazine) {
            cnt[i - 'a']++;
        }
        for (char& j: ransomNote) {
            cnt[j - 'a']--;
            if (cnt[j - 'a'] < 0) {
                // 这个字母在magazine中找不到这么多个
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

