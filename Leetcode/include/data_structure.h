#ifndef LEETCODE_DATA_STRUCTURE_H
#define LEETCODE_DATA_STRUCTURE_H

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

#endif //LEETCODE_DATA_STRUCTURE_H
