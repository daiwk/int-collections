/*
 * @lc app=leetcode.cn id=124 lang=cpp
 *
 * [124] 二叉树中的最大路径和
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
    int max_sum = INT_MIN; //需要初始化为INT_MIN，因为如果整棵树全为负，max_sum得小于0
    int max_gain(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        int left_gain = max(max_gain(root->left), 0);
        int right_gain = max(max_gain(root->right), 0);
        // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值, 这里是加！！，因为可以左边走上来，再往右边走下去
        int cur_max_gain = root->val + left_gain + right_gain;
        max_sum = max(max_sum, cur_max_gain);
        // 这里是max，因为定义的时候，是以root为起点，不能回头，所以只有一个方向 
        return root->val + max(left_gain, right_gain);
    }
    int maxPathSum(TreeNode* root) {
        max_gain(root);
        return max_sum;
    }
};
// @lc code=end

