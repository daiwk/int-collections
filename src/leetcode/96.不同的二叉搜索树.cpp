/*
 * @lc app=leetcode.cn id=96 lang=cpp
 *
 * [96] 不同的二叉搜索树
 */

// @lc code=start
class Solution {
public:
    int numTrees(int n) {
        vector<int> G(n + 1, 0);
        G[0] = 1;// 空树，只有一个解
        G[1] = 1;// 只有根，只有一个解
        for (int i = 2; i <= n; i++) { // 从2开始，因为前面算了0和1
            for (int j = 1; j <= i; j++) { 
                // 从1开始，因为要j-1>=0;
                // <=i，因为要i-j>=0
                G[i] += G[j - 1] * G[i - j]; 
            }
       }
       return G[n];
    }
};
// @lc code=end

