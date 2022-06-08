/*
 * @lc app=leetcode.cn id=138 lang=cpp
 *
 * [138] 复制带随机指针的链表
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> xmap;
        Node* cur = head;
        while (cur != nullptr) {
            Node* tmp = new Node(cur->val);
            xmap[cur] = tmp;
            cur = cur->next;
        }
        cur = head;
        while (cur != nullptr) {
            xmap[cur]->next = xmap[cur->next];
            xmap[cur]->random = xmap[cur->random];
            cur = cur->next;
        }
        return xmap[head];
    }
};
// @lc code=end

