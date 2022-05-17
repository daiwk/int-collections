/*
 * @lc app=leetcode.cn id=543 lang=cpp
 *
 * [543] 二叉树的直径
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
    // 经过节点的最长路径就是左孩子深度+右孩子深度，
    /// 因此，求出所有节点的最长路径，取个max就是了
    // 而求深度可以用递归的dfs，depth返回的是max(左深度,右深度)+1
    int depth_max = 0;
    int depth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int left_depth = depth(root->left);
        int right_depth = depth(root->right);
        int cur_depth = left_depth + right_depth;
        depth_max = max(depth_max, cur_depth);
        return max(left_depth, right_depth) + 1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        depth(root);
        return depth_max;
    }
};
// @lc code=end

