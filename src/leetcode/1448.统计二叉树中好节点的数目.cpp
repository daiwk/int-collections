/*
 * @lc app=leetcode.cn id=1448 lang=cpp
 *
 * [1448] 统计二叉树中好节点的数目
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
    int goodNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return good_nodes_sub(root, root->val);
    }
    int good_nodes_sub(TreeNode* root, int max_val) {
        if (root == nullptr) {
            return 0;
        }
        int ret = 0;
        if (root->val >= max_val) {
            max_val = root->val;
            ret++;
        }
        return good_nodes_sub(root->left, max_val) + good_nodes_sub(root->right, max_val) + ret;
    }

};
// @lc code=end

