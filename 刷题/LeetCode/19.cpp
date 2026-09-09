class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* p = head;
		vector<int> tmp;
		while (p!=nullptr)
		{
			tmp.push_back(p->val);
			p = p->next;a
		}
		tmp.erase(tmp.end() - n);
		int tmpsize = tmp.size();
		ListNode* last = nullptr;
		ListNode* now = nullptr;
		for (int i = tmpsize - 1;i >= 0;i--) {
			last = now;
			now = new ListNode(tmp[i], last);
		}
		return now;
	}
};