/*
 * @lc app=leetcode.cn id=94 lang=cpp
 *
 * [94] 二叉树的中序遍历
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
    // 递归
    // vector<int> inorderTraversal(TreeNode* root) {
    //     vector<int> res;
    //     inorder(root, res);
    //     return res;
    // }
    // void inorder(TreeNode* root, vector<int>& res) {
    //     if (root == nullptr) {
    //         return;
    //     }
    //     inorder(root->left, res);
    //     res.push_back(root->val);
    //     inorder(root->right, res);
    // }
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
};
// @lc code=end

