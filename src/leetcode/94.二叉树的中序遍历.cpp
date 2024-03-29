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
        while (!stk.empty() || root != nullptr) {
            //先把左都塞进去
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            // 取出根，给res
            root = stk.top();
            stk.pop();
            res.push_back(root->val);
            // 再搞右
            root = root->right;
        }
        return res;
    }
};
// @lc code=end

