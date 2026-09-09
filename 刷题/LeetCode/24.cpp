class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* list = new ListNode(0, head);
        ListNode* p = list, * q = head;
        while (q&&q->next)
        {
            ListNode* node = q->next;
            ListNode* node2 = node->next;
            p->next = node;
            node->next = q;
            q->next = node2;
            p = q;
            q = node2;
        }
        return list->next;
    }
};