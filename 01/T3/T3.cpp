#include <iostream>

// 定义单链表节点结构
struct ListNode {
    int data;
    ListNode* next;
    ListNode(int val) : data(val), next(nullptr) {}
};


ListNode* createList(int arr[], int n) {
    if (n == 0) {
        return nullptr;
    }
    ListNode* head = new ListNode(arr[0]);
    ListNode* current = head;
    for (int i = 1; i < n; ++i) {
        current->next = new ListNode(arr[i]);
        current = current->next;
    }
    return head;
}


void printList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "NULL" << std::endl;
}


ListNode* mergeToDescending(ListNode* listA, ListNode* listB) {
    ListNode* headC = nullptr; // 结果链表 C 的头指针

    // 只要两个链表都还有节点，就进行比较
    while (listA != nullptr && listB != nullptr) {
        ListNode* temp = nullptr;
        // 比较两个链表的当前节点，取较小的一个
        // 当有相同元素时，优先取 listA 的节点
        if (listA->data <= listB->data) {
            temp = listA;
            listA = listA->next; // listA 指针后移
        }
        else {
            temp = listB;
            listB = listB->next; // listB 指针后移
        }

        // 使用头插法将取出的节点插入到 C 的头部
        temp->next = headC;
        headC = temp;
    }

    // 处理 listA 中剩余的节点
    while (listA != nullptr) {
        ListNode* temp = listA;
        listA = listA->next;
        temp->next = headC;
        headC = temp;
    }

    // 处理 listB 中剩余的节点
    while (listB != nullptr) {
        ListNode* temp = listB;
        listB = listB->next;
        temp->next = headC;
        headC = temp;
    }

    return headC;
}

int main() {
    // --- 测试用例 1: 基本情况 ---
    int arrA[] = { 2, 5, 8, 10 };
    int arrB[] = { 1, 3, 7, 9 };
    ListNode* listA = createList(arrA, 4);
    ListNode* listB = createList(arrB, 4);

    std::cout << "--- 测试用例 1 ---" << std::endl;
    std::cout << "输入链表 A: ";
    printList(listA);
    std::cout << "输入链表 B: ";
    printList(listB);

    ListNode* listC = mergeToDescending(listA, listB);

    std::cout << "归并后的递减链表 C: ";
    printList(listC);
    std::cout << std::endl;

    // --- 测试用例 2: 包含相同元素 ---
    int arrA2[] = { 1, 5, 5, 12 };
    int arrB2[] = { 3, 5, 10, 15 };
    ListNode* listA2 = createList(arrA2, 4);
    ListNode* listB2 = createList(arrB2, 4);

    std::cout << "--- 测试用例 2 (包含相同元素) ---" << std::endl;
    std::cout << "输入链表 A: ";
    printList(listA2);
    std::cout << "输入链表 B: ";
    printList(listB2);

    ListNode* listC2 = mergeToDescending(listA2, listB2);

    std::cout << "归并后的递减链表 C: ";
    printList(listC2);
    std::cout << std::endl;

    // --- 测试用例 3: 其中一个链表为空 ---
    int arrA3[] = { 10, 20, 30 };
    ListNode* listA3 = createList(arrA3, 3);
    ListNode* listB3 = nullptr;

    std::cout << "--- 测试用例 3 (一个链表为空) ---" << std::endl;
    std::cout << "输入链表 A: ";
    printList(listA3);
    std::cout << "输入链表 B: ";
    printList(listB3);

    ListNode* listC3 = mergeToDescending(listA3, listB3);

    std::cout << "归并后的递减链表 C: ";
    printList(listC3);
    std::cout << std::endl;

    
    return 0;
}
