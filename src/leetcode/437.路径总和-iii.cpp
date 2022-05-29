/*
 * @lc app=leetcode.cn id=437 lang=cpp
 *
 * [437] 路径总和 III
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
    unordered_map<long long, int> prefix;

    int dfs(TreeNode* root, long long cur, int target) {
        int ret = 0;
        if (root == nullptr) {
            return 0;
        }
        cur += root->val;

        if (prefix.count(cur - target)) {
            ret = prefix[cur - target];
        }
        // count完之后才能++，要不target=0的时候，就错了
        prefix[cur]++;
        ret += dfs(root->left, cur, target);
        ret += dfs(root->right, cur, target);
        prefix[cur]--;
        return ret;
    }

    int pathSum(TreeNode* root, int targetSum) {
        // 很关键，为了使每个=target的节点都能成为一条路径（自己到自己）
        // 即cur-target=0的情况
        prefix[0] = 1;
        return dfs(root, 0, targetSum);
    }
};
// @lc code=end

