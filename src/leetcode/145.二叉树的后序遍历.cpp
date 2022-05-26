/*
 * @lc app=leetcode.cn id=145 lang=cpp
 *
 * [145] 二叉树的后序遍历
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        TreeNode* prev = nullptr;
        while (!stk.empty() || root != nullptr) {
            //先把左都塞进去
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            // 取出根
            root = stk.top();
            stk.pop();
            // 再搞右
            if (root->right == nullptr || prev == root->right) {
                // 当前节点已经没有右子树了，且上一个节点就是它的右子树
                // 这个时候主是我们要的结果了
                res.push_back(root->val);
                // 更新prev为当前节点，并重置root为null
                prev = root;
                root = nullptr;
            } else {
                //root扔进去，访问右子树
                stk.push(root);
                root = root->right;
            }
        }
        return res;
    }
};
// @lc code=end

