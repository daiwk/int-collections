# 数组

# 链表

# 树

## 中序遍历
栈
一直塞左子树，取出栈顶，扔到res里去，pop出来，开始遍历原栈顶的右子树

```c++
vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        vector<int> res;
        while (root != nullptr || !stk.empty()) { // 两个条件 或！！！！
            while (root != nullptr) { // 一直把root的左子树丢进去
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop(); // 栈顶扔出来
            res.emplace_back(root->val); // 值搞进去
            root = root->right; // 开始原栈顶的右子树
        }
        return res;
    }
```

## 层序遍历
队列（bfs）queue


## 锯齿形层序遍历
队列+优先队列deque

## 前序+中序还原树

前序：根 [左][右]
中序：[左] 根 [右]
找到根在中序里的位置（先用map存好值-位置关系，o1查），然后递归

## 二叉搜索树第k小

左边比根小，右边比根大，那就中序遍历，遍历完成左，然后根，然后右，然后k--，减到0就是了
中序就是栈

# 图

## dfs

岛屿数量：以1开始，dfs，visited置0，dfs就是上下左右地递归：

```c++
   void dfs(vector<vector<char> >& grid, int r, int c) {
        int rows = grid.size();
        int cols = grid[0].size();
        grid[r][c] = '0';
        if (r -1 >= 0 && grid[r - 1][c] == '1') {
            dfs(grid, r - 1, c); // 上
        }
        if (r + 1 < rows && grid[r + 1][c] == '1') {
            dfs(grid, r + 1, c); // 下
        }
        if (c - 1 >= 0 && grid[r][c - 1] == '1') {
            dfs(grid, r, c - 1); // 左
        }
        if (c + 1 < cols && grid[r][c + 1] == '1') {
            dfs(grid, r, c+1); // 右
        }
    }
```

# 回溯法

回溯法：一种通过探索所有可能的候选解来找出所有的解的算法。如果候选解被确认不是一个解（或者至少不是最后一个解），回溯算法会通过在上一步进行一些变化抛弃该解，即回溯并且再次尝试。

套路：
调用：

```c++
        vector<string> res;
        string cur;
        backtrace(res, cur, xxx);
        return res;
```

回溯函数：

```c++
    void backtrace(vector<string>& res, string& cur, xxx) {
        if (aaaa) {
            res.push_back(cur);
            return;
        }
        if (bbbb) {
            cur.push_back('aaa');
            backtrace(res, cur, xxxx); // xxxx可能是+1 -1之类的操作
            cur.pop_back();
        }
    }
```

## 全排列

```c++
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > res;
        backtrace(res, nums, 0, nums.size());
        return res;
    }
    void backtrace(vector<vector<int> >& res, vector<int>& output, int first, int len) {
        if (first == len) {
            res.push_back(output);
        }
        for (int i = first; i < len; ++i) {
            swap(output[i], output[first]); // 交换
            backtrace(res, output, first + 1, len);
            swap(output[i], output[first]); // 换回去
        }
    }
```

# dp
