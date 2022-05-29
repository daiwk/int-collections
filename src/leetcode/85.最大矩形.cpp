/*
 * @lc app=leetcode.cn id=85 lang=cpp
 *
 * [85] 最大矩形
 */

// @lc code=start
class Solution {
public:
    int max_hist(vector<int> &heights)
    {
        int n = heights.size();
        vector<int> left(n), right(n, n);
        stack<int> mono_stk;
        for (int i = 0; i < n; ++i)
        {
            while (!mono_stk.empty() && heights[mono_stk.top()] >= heights[i])
            {
                right[mono_stk.top()] = i;
                mono_stk.pop();
            }
            left[i] = mono_stk.empty() ? -1 : mono_stk.top();
            mono_stk.push(i);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }

    int maximalRectangle(vector<vector<char> > &matrix)
    {
        int rows = matrix.size();
        if (rows == 0)
        {
            return 0;
        }
        int cols = matrix[0].size();
        int res = 0;
        for (int i = 0; i < rows; ++i)
        {
            vector<int> heights(cols);
            for (int j = 0; j < cols; ++j)
            {
                int k = i;
                while (matrix[k][j] == '1')
                {
                    heights[j]++;
                    // cout << j << " " << k << endl;
                    if (k == 0)
                    {
                        // 注意这个的位置，得在heights[j]++之后
                        // 否则如果这个矩阵里就一个元素1的时候，就gg了
                        break;
                    }
                    k--;
                }
                res = max(res, max_hist(heights));
            }
        }
        return res;
    }
};
// @lc code=end

