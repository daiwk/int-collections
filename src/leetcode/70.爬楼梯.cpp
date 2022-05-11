/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */

// @lc code=start
class Solution {
public:
    int climbStairs(int n) {
        // 斐波那契
        int p= 0, q = 0, r = 1;
        // 注意，这里是从1开始，相当于把上面那三个数往右平移一格
        // i<=n，注意有等号
        for (int i = 1; i <= n; ++i) {
            p = q;
            q = r;
            r = p + q;
        }
        return r;
    }
};
// @lc code=end

