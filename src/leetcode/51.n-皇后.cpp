/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string> > solutions = vector<vector<string> >();
        vector<int> queens = vector<int>(n, -1); //初始化都是-1
        unordered_set<int> columns;
        unordered_set<int> diagonals1;
        unordered_set<int> diagonals2;
        backtrack(solutions, queens, n, 0, columns, diagonals1, diagonals2);
        return solutions;
    }

    vector<string> generate_board(vector<int>& queens, int n) {
        vector<string> board;
        for (int i = 0; i < n; ++i) {
            string row = string(n, '.'); // 初始化为n个.
            row[queens[i]] = 'Q';
            board.push_back(row);
        }
        return board;
    }
    void backtrack(vector<vector<string> > &solutions, vector<int>& queens, 
        int n, int row, unordered_set<int>& columns, 
        unordered_set<int>& diagonals1, unordered_set<int> diagonals2) {
        if (row == n) {
            vector<string> board = generate_board(queens, n); 
            solutions.push_back(board);
        } else {
            for (int i = 0; i < n; ++i) {
                if (columns.count(i)) {
                    continue;
                }
                int diagonal1 = row - i;
                if (diagonals1.count(diagonal1)) {
                    continue;
                }
                int diagonal2 = row + i;
                if (diagonals2.count(diagonal2)) {
                    continue;
                }
                queens[row] = i; // 放进来试试
                columns.insert(i); // 这一列不能继续放
                diagonals1.insert(diagonal1); // 左上角不能继续放
                diagonals2.insert(diagonal2); // 右上角不能继续放
                backtrack(solutions, queens, n, row + 1, columns, diagonals1, diagonals2);
                // 还原
                queens[row] = -1;
                columns.erase(i); 
                diagonals1.erase(diagonal1);
                diagonals2.erase(diagonal2);
            }
        }
    }
};
// @lc code=end

