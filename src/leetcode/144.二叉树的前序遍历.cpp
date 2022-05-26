/*
 * @lc app=leetcode.cn id=144 lang=cpp
 *
 * [144] 二叉树的前序遍历
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        std::stack<TreeNode*> stk;
        while (!stk.empty() || root != nullptr) {
            //先把左都塞进去
            while (root != nullptr) {
                stk.push(root);
                // 改成left的时候就塞了！！
                res.push_back(root->val);
                root = root->left;
            }
            // 取出根
            root = stk.top();
            stk.pop();
            // 再搞右
            root = root->right;
        }
        return res;
    }
};
// @lc code=end

