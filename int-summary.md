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

# dp
