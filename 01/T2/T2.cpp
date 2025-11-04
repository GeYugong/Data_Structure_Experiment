#include <iostream>
#include <vector>
#include <algorithm> // 用于 std::max

// 定义单链表的节点结构
struct Node {
    int data;
    Node* next;

    // 构造函数，方便创建新节点
    Node(int val) : data(val), next(nullptr) {}
};

// (1) 递归算法：求链表中的最大值
// 前提：链表不为空
int findMax(Node* head) {
    // 基准条件：如果这是链表的最后一个节点，那么它就是最大值
    if (head->next == nullptr) {
        return head->data;
    }
    // 递归步骤：找出剩余链表部分的最大值
    int maxInRest = findMax(head->next);
    // 返回当前节点值与剩余部分最大值中的较大者
    return std::max(head->data, maxInRest);
}

// (2) 递归算法：求链表中的结点个数
int countNodes(Node* head) {
    // 基准条件：如果链表为空，节点数为0
    if (head == nullptr) {
        return 0;
    }
    // 递归步骤：返回 1 (当前节点) + 剩余链表的节点数
    return 1 + countNodes(head->next);
}

// 用于计算平均值的辅助递归函数：求所有整数的和
long long sumNodes(Node* head) {
    // 基准条件：如果链表为空，和为0
    if (head == nullptr) {
        return 0;
    }
    // 递归步骤：返回 当前节点的值 + 剩余链表的和
    return head->data + sumNodes(head->next);
}

// (3) 运算：求所有整数的平均值 (利用上面的递归函数)
int calculateAverage(Node* head) {
    if (head == nullptr) {
        return 0;
    }
    long long totalSum = sumNodes(head);
    int totalCount = countNodes(head);

    // 避免除以零错误
    if (totalCount == 0) {
        return 0;
    }

    // 根据结果图，返回整型平均值
    return static_cast<int>(totalSum / totalCount);
}

// 辅助函数：打印链表内容，格式与图片一致
void printList(Node* head) {
    Node* current = head;
    int index = 0;
    std::cout << "list" << std::endl;
    while (current != nullptr) {
        std::cout << index << ": " << current->data << std::endl;
        current = current->next;
        index++;
    }
}

// 辅助函数：释放链表占用的内存
void deleteList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

int main() {
    // 设置本地化，以正确显示中文（如果需要）
    // setlocale(LC_ALL, "");

    // 创建链表
    std::vector<int> values = { 1, 2, 6, 8, 9, 90, 397, 13, 434, 77 };
    Node* head = nullptr;
    Node* tail = nullptr;

    for (int val : values) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // --- 开始输出---
    std::cout << "begin..." << std::endl;
    std::cout << "====================" << std::endl;

    printList(head);


    std::cout << "total: " << countNodes(head) << std::endl;

    std::cout << "====================" << std::endl;

    if (head != nullptr) {
        // (1) 求最大值并输出
        int maxValue = findMax(head);
        std::cout << "max value is: " << maxValue << std::endl;

        // (2) 求结点个数并输出
        int listSize = countNodes(head);
        std::cout << "list size is: " << listSize << std::endl;

        // (3) 求平均值并输出
        int averageValue = calculateAverage(head);
        std::cout << "average value is: " << averageValue << std::endl;
    }
    else {
        std::cout << "list is empty." << std::endl;
    }

    std::cout << "end" << std::endl;

    // --- 释放内存 ---
    deleteList(head);

    // 在Visual Studio调试时暂停控制台
    // system("pause"); 

    return 0;
}