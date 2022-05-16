/*
 * @lc app=leetcode.cn id=199 lang=cpp
 *
 * [199] 二叉树的右视图
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
    // // bfs版本
    // vector<int> rightSideView(TreeNode* root) {
    //     unordered_map<int, int> right_map;
    //     int max_depth = -1;
    //     queue<TreeNode*> node_q;
    //     queue<int> depth_q;
    //     node_q.push(root);
    //     depth_q.push(0);
    //     while (!node_q.empty()) {
    //         TreeNode* node = node_q.front();
    //         node_q.pop();
    //         int depth = depth_q.front();
    //         depth_q.pop();
    //         if (node != nullptr) {
    //             // 记录最大深度
    //             max_depth = max(max_depth, depth);
    //             // 不断更新，最后一个就是最右边的了
    //             right_map[depth] = node->val;
    //             // left right都要扔进去，且都要扔depth+1进去
    //             node_q.push(node->left);
    //             depth_q.push(depth + 1);
    //             node_q.push(node->right);
    //             depth_q.push(depth + 1);
    //         }
    //     }
    //     vector<int> res;
    //     for (int depth = 0; depth <= max_depth; ++depth) {
    //         res.push_back(right_map[depth]);
    //     }
    //     return res;
    // }
    // dfs版本
    vector<int> rightSideView(TreeNode* root) {
        unordered_map<int, int> right_map;
        int max_depth = -1;
        stack<TreeNode*> node_stk;
        stack<int> depth_stk;
        node_stk.push(root);
        depth_stk.push(0);
        while (!node_stk.empty()) {
            TreeNode* node = node_stk.top();
            node_stk.pop();
            int depth = depth_stk.top();
            depth_stk.pop();
            if (node != nullptr) {
                max_depth = max(max_depth, depth);
                // 只搞一次
                if (right_map.find(depth) == right_map.end()) {
                    right_map[depth] = node->val;
                }
                // stk是后进先出，所以先left再right
                node_stk.push(node->left);
                node_stk.push(node->right);
                depth_stk.push(depth + 1);
                depth_stk.push(depth + 1);
            }
        }
        vector<int> res;
        for (int depth = 0; depth <= max_depth; ++depth) {
            res.push_back(right_map[depth]);
        }
        return res;
    }
};
// @lc code=end

