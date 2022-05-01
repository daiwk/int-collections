/*
 * @lc app=leetcode.cn id=103 lang=cpp
 *
 * [103] 二叉树的锯齿形层序遍历
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        // 层序遍历，加个参数，奇数左到右，偶数右到左
        // dequeue，双端队列
        vector<vector<int> > res;
        if (root == nullptr) {
            return res;
        }
        queue<TreeNode*> q;
        q.push(root);
        bool left_order = true;
        while (!q.empty()) {
            deque<int> level_lst;
            int size = q.size();
            for (int i = 0; i < size; ++i) { // 这里写size，而不是q.size，因为q一直在变！！！
                TreeNode* node = q.front();
                q.pop();
                if (left_order) {
                    level_lst.push_back(node->val);
                } else {
                    level_lst.push_front(node->val);
                }
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            res.emplace_back(vector<int>(level_lst.begin(), level_lst.end()));
            left_order = !left_order;
        }
        return res;
    }
};
// @lc code=end

