/*
 * @lc app=leetcode.cn id=85 lang=cpp
 *
 * [85] 最大矩形
 */

// @lc code=start
class Solution {
public:

    int maxArea(vector<int>& heights, int start, int end) {
        if (start > end) {
            return 0;
        } 
        int min_idx = start;
        int min_hight = heights[start];
        for (int i = start; i <= end; ++i) {
            if (min_hight > heights[i]) {
                min_idx = i;
                min_hight = heights[i];
            }
        }
        return std::max(std::max(min_hight * (end - start + 1), maxArea(heights, start, min_idx - 1)), maxArea(heights, min_idx + 1, end));

    }
    int largestRectangleArea(vector<int>& heights) {
        if (heights.size() == 0) {
            return 0;
        }
        return maxArea(heights, 0, heights.size() - 1);
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = 0;
        if (rows > 0) {
            cols = matrix[0].size();
        }
        if (rows == 0 || cols == 0) {
            return 0;
        }
        int maxmax = 0;
        for (int i = 0; i < rows; ++i) {
            vector<int> heights;
            for (int j = 0; j < cols; ++j) {
                int cur_height = 0;
                if (matrix[i][j] == '1') {
                    for (int k = i; k >= 0; --k) {
                        if (matrix[k][j] == '0') {
                            break;
                        } 
                        ++cur_height;
                    }
                }
                heights.emplace_back(cur_height);
            }
            maxmax = std::max(maxmax, largestRectangleArea(heights));
        }
        return maxmax;
    }
};
// @lc code=end

