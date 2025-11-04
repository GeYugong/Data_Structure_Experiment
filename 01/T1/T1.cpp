#include <iostream>
#include <vector>

// 定义链表结点结构
struct LNode {
    int data;
    LNode* next;
    // 构造函数，方便创建新结点
    LNode(int val) : data(val), next(nullptr) {}
};

// 函数：查找单链表（带头结点）的倒数第 k 个结点
// head: 链表的头结点
// k: 倒数的位置
// index: 用于返回找到的结点的索引（通过引用传递）
LNode* findKthFromEnd(LNode* head, int k, int& index) {
    if (head == nullptr || k <= 0) {
        index = -1;
        return nullptr;
    }

    LNode* fast = head->next;
    LNode* slow = head->next;

    // 1. 快指针先向前移动 k-1 步
    for (int i = 0; i < k - 1; ++i) {
        if (fast != nullptr) {
            fast = fast->next;
        }
        else {
            // 如果链表长度小于 k，则返回空
            index = -1;
            return nullptr;
        }
    }

    // 如果快指针在移动后为空，说明链表长度恰好为 k-1，也无法找到
    if (fast == nullptr) {
        index = -1;
        return nullptr;
    }

    // 2. 快慢指针同步移动，直到 fast 到达链表末尾
    int currentIndex = 0;
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
        currentIndex++;
    }

    // 此时 slow 指向的就是倒数第 k 个结点
    // currentIndex 记录了 slow 指针从头移动的步数，即为索引
    index = currentIndex;
    return slow;
}

// 辅助函数：这个函数接收一个整数向量 values，并据此创建一个带头结点的链表
LNode* createList(const std::vector<int>& values) {
    LNode* head = new LNode(0); // 创建头结点
    LNode* current = head;
    for (int val : values) {//遍历 values 向量中的每一个整数
        current->next = new LNode(val);
        current = current->next;
    }
    return head;
}

// 辅助函数：打印链表
void printList(LNode* head, int& total) {
    LNode* current = head->next;
    int i = 0;
    std::cout << "list" << std::endl;
    while (current != nullptr) {
        std::cout << i << ": " << current->data << std::endl;
        current = current->next;
        i++;
    }
    total = i;
}

int main() {
    std::cout << "begin..." << std::endl;
    int k = 2;
    std::cout << "k: " << k << std::endl;
    std::cout << "================" << std::endl;

    // 根据图片中的数据创建链表
    std::vector<int> values = { 1, 2, 6, 8, 9, 90, 397, 666, 13, 434, 77, -100 };
    LNode* head = createList(values);

    // 打印链表并计算总数
    int total_nodes = 0;
    printList(head, total_nodes);
    std::cout << "total: " << total_nodes << std::endl;
    std::cout << std::endl;

    int foundIndex = -1;
    LNode* resultNode = findKthFromEnd(head, k, foundIndex);

    if (resultNode != nullptr) {
        std::cout << "index: " << foundIndex << " value: " << resultNode->data << std::endl;
    }
    else {
        std::cout << "Could not find the " << k << "-th node from the end." << std::endl;
    }

    std::cout << "end" << std::endl;

    // 清理内存
    LNode* current = head;
    while (current != nullptr) {
        LNode* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}