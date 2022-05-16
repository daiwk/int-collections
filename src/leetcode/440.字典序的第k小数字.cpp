/*
 * @lc app=leetcode.cn id=440 lang=cpp
 *
 * [440] 字典序的第K小数字
 */

// @lc code=start
class Solution {
public:
    int get_steps(int cur, long n) {
        int steps = 0;
        long first = cur; //long?
        long last = cur;
        // 层次遍历
        while (first <= n) {
            steps += min(last, n) - first + 1;
            first = first * 10;
            last = last * 10 + 9;
        }
        return steps;
    }

    int findKthNumber(int n, int k) {
        int cur = 1;
        k--;
        while (k > 0) {
            int steps = get_steps(cur, n);
            if (steps <= k) {
                k -= steps;// 跳过当前子树，往右走
                cur++;
            } else {
                cur = cur * 10;//进入左子树
                k--;
            }
        }
        return cur;
    }
};
// @lc code=end

