/*
 * @lc app=leetcode.cn id=236 lang=cpp
 *
 * [236] 二叉树的最近公共祖先
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    unordered_map<int, TreeNode*> father_map;
    unordered_set<int> path;

    void dfs(TreeNode* root) {
        if (root->left != nullptr) {
            father_map[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right != nullptr) {
            father_map[root->right->val] = root;
            dfs(root->right);
        }
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 根节点没有father
        father_map[root->val] = nullptr;
        dfs(root);
        while (p != nullptr) {
            path.emplace(p->val);
            p = father_map[p->val];
        }
        while (q != nullptr) {
            if (path.find(q->val) != path.end()) {
                return q;
            }
            q = father_map[q->val];
        }
        return q;
    }
};
// @lc code=end

