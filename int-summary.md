## 数组

## 链表

## 树

中序遍历：栈

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
            root = root->right; // 开始右子树
        }
        return res;
    }
```

层序遍历：队列（bfs） queue

锯齿形层序遍历：队列+优先队列deque



## 图

## dp
