/*
 * @lc app=leetcode.cn id=48 lang=cpp
 *
 * [48] 旋转图像
 */

// @lc code=start
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        if (rows == 0) {
            return;
        }
        int cols = matrix[0].size();
        // 水平翻转
        for (int i = 0; i < rows / 2; ++i) { 
            // 注意是rows/2!!
            for (int j = 0; j < cols; ++j) {
                swap(matrix[i][j], matrix[rows - 1 - i][j]);
            }
        }
        // 对角线翻转
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < i; ++j) { 
                // 注意是j < i!!
                swap(matrix[j][i], matrix[i][j]);
            }
        }
        return;
    }
};
// @lc code=end

