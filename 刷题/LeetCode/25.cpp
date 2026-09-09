class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        int n=0;
        ListNode* List=head;
        while (List)
        {
            n++;
            List = List->next;
        }
        List = new ListNode(0, head);
        ListNode* LastTail = List;
        for (;n >= k;n -= k) {
            ListNode* Pre = nullptr;
            ListNode* Now=LastTail->next;
            for (int i = 0;i < k;i++) {
                ListNode* Next = Now->next;
                Now->next = Pre;
                Pre = Now;
                Now = Next;
            }
            ListNode* Tail = LastTail->next;
            Tail->next = Now;
            LastTail->next = Pre;
            LastTail = Tail;
        }
        return List->next;
    }
};