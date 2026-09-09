class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<int> pq;
        for (auto i : lists) {
            while (i!=nullptr)
            {
                pq.push(i->val);
                i = i->next;
            }
        }
        ListNode* now = nullptr;
        ListNode* last = nullptr;
        while (!pq.empty())
        {
            last = now;
            now = new ListNode(pq.top(), last);
            pq.pop();
        }
        return now;
    }  
};