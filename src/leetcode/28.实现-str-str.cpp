/*
 * @lc app=leetcode.cn id=28 lang=cpp
 *
 * [28] 实现 strStr()
 */

// @lc code=start
class Solution {
public:
    int strStr(string haystack, string needle) {
        int len_1 = haystack.size();
        int len_2 = needle.size();
        if (len_2 == 0) return 0;
        for (int i = 0; i < len_1 - len_2 + 1; ++i) {
            int j = i;
            int k = 0;
            while (haystack[j++] == needle[k++]) {
                if (k == len_2) {
                    return i;
                }
            }
        }
        return -1;
    }
};
// @lc code=end

