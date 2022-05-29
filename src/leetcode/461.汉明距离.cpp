/*
 * @lc app=leetcode.cn id=461 lang=cpp
 *
 * [461] 汉明距离
 */

// @lc code=start
class Solution {
public:
    int hammingDistance(int x, int y) {
        int cnt = 0;
        int s = x ^ y;
        while (s) {
            s = s & (s - 1);
            cnt++;
        }
        return cnt;
    }
};
// @lc code=end

