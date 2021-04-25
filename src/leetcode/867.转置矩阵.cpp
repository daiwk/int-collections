/*
 * @lc app=leetcode.cn id=867 lang=cpp
 *
 * [867] 转置矩阵
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& A) {
        vector<vector<int> > res;
        int row_size = A.size();
        int col_size = A[0].size();
        for (int i = 0; i < col_size; ++i) {
            vector<int> tmp_vec;
            for (int j = 0; j < row_size; ++j) {
                tmp_vec.push_back(A[j][i]);
            }
            res.push_back(tmp_vec);
        }
        return res;
    }
};
// @lc code=end

