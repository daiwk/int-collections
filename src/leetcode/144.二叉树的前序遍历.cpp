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
        vector<int> ret;
        std::stack<TreeNode*> st;
        //ret.push_back(root->val);
        st.push(root);
        while (!st.empty()) {
            TreeNode* tmp = st.top();
            st.pop();
            if (tmp) {
                ret.push_back(tmp->val);
            }
            else {
                break;
            }
            if (tmp->right) {
                st.push(tmp->right);
            }
            if (tmp->left) {
                st.push(tmp->left);
            }
        }
        return ret;
    }
};
// @lc code=end

