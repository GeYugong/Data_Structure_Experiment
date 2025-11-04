#include <iostream>
#include <queue>
using namespace std;

//计算并打印(a+b)^k展开后的系数
void print_binomial_coefficients(int k) {
    queue<int> q;

    // 初始状态：(a+b)^0 的系数是 1
    q.push(1);

    // 通过循环，从第 1 行迭代计算到第 k 行
    for (int i = 1; i <= k; ++i) {
        // 此时，队列 q 中存储的是 (a+b)^(i-1) 的系数

        // 1. 在队尾添加一个0作为处理结束的标志
        q.push(0);

        // 2. 准备一个变量 prev，代表逻辑上的“前导0”
        int prev = 0;

        // 3. 迭代生成新一行的系数
        // 对于第 i-1 行（有 i 个系数），加上尾部的0，共需处理 i+1 次
        // 以生成第 i 行的 i+1 个新系数。
        for (int j = 0; j <= i; ++j) {
            // 取出队首元素
            int curr = q.front();
            q.pop();

            // 新系数是前一个元素和当前元素的和 [cite: 273]
            // 例如，由 [1, 2, 1] 生成 [1, 3, 3, 1]
            // 1=0+1, 3=1+2, 3=2+1, 1=1+0
            q.push(prev + curr);

            // 更新 prev，为计算下一个系数做准备
            prev = curr;
        }
    }

    // 循环结束后，队列中存储的就是(a+b)^k的最终系数
    cout << "k=" << k << "时, (a+b)的" << k << "次方展开式各项系数为：" << endl;
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int main() {
    int k;
    cout << "请输入k的值（k>=2）：" << endl;
    cin >> k;

    if (k >= 2) {
        print_binomial_coefficients(k);
    }
    else {
        cout << "输入值不符合要求，k必须大于等于2。" << endl;
    }

    return 0;
}
//         1 < --k = 0
//        / \
//       1---1 < --k = 1
//      / \ / \
//     1---2---1 < --k = 2 (2 = 1 + 1)
//    / \ / \ / \
//   1---3---3---1 < --k = 3 (3 = 1 + 2, 3 = 2 + 1)
//  / \ / \ / \ / \
//1-- - 4-- - 6-- - 4-- - 1 < --k = 4 (4 = 1 + 3, 6 = 3 + 3, 4 = 3 + 1)
//i = 3
////1-- - 2-- - 1
//q = [1, 2, 1, 0], prev = 0
//
//j = 0:
//curr = q.front(); (curr = 1)
//q.pop(); (q 变为[2, 1, 0])
//q.push(prev + curr); (q 中推入 0 + 1 = 1, q 变为[2, 1, 0, 1])
//prev = curr; (prev 更新为 1)
//解读：新一行的第一个系数 1 被计算出来并放到了队尾。
//
//j = 1:
//curr = q.front(); (curr = 2)
//q.pop(); (q 变为[1, 0, 1])
//q.push(prev + curr); (q 中推入 1 + 2 = 3, q 变为[1, 0, 1, 3])
//prev = curr; (prev 更新为 2)
//解读：新一行的第二个系数 3 被计算出来并放到了队尾。
//
//j = 2:
//curr = q.front(); (curr = 1)
//q.pop(); (q 变为[0, 1, 3])
//q.push(prev + curr); (q 中推入 2 + 1 = 3, q 变为[0, 1, 3, 3])
//prev = curr; (prev 更新为 1)
//解读：新一行的第三个系数 3 被计算出来并放到了队尾。
//
//j = 3:
//curr = q.front(); (curr = 0, 这是我们之前放进去的标记)
//q.pop(); (q 变为[1, 3, 3])
//q.push(prev + curr); (q 中推入 1 + 0 = 1, q 变为[1, 3, 3, 1])
//prev = curr; (prev 更新为 0)
//解读：新一行的最后一个系数 1 被计算出来并放到了队尾。