/*
 * @lc app=leetcode.cn id=98 lang=cpp
 *
 * [98] 验证二叉搜索树
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
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stk;
        // 用long long，背下来。。
        long long inorder_last = (long long)INT_MIN - 1;
        // 两个条件
        while (!stk.empty() || root != nullptr) {
            while (root != nullptr) {
                stk.push(root);
                // 先把左子树全塞进去
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (root->val <= inorder_last) {
                return false;
            }
            inorder_last = root->val; // 中序的last
            root = root->right;
        }
        return true;
    }
};
// @lc code=end

