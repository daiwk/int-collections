/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> vec;
        while (head != NULL) {
            vec.emplace_back(head->val);
            head = head->next;
        }
        std::reverse(vec.begin(), vec.end());
        return vec;
    }
};
