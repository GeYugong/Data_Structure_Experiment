#include <iostream>
#include <stack>
#include <string>
using namespace std;

// 判断是否为运算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 获取运算符优先级
int getPriority(char op) {
    if (op == '*' || op == '/') {
        return 2;
    }
    else if (op == '+' || op == '-') {
        return 1;
    }
    return 0;
}

// 中缀表达式转后缀表达式
//1.遇到数字：直接输出到后缀表达式
//2.遇到左括号(：直接入栈
//3.遇到右括号)：弹出栈中元素直到遇到左括号
//4.遇到运算符：弹出所有优先级 ≥ 当前运算符的栈顶元素，然后当前运算符入栈
//5.表达式结束：弹出栈中所有剩余运算符
string infixToPostfix(const string& infix) {
    stack<char> opStack;
    string postfix;

    for (char c : infix) {
        if (c == ' ') { // 跳过空格
            continue;
        }
        else if (isdigit(c)) { // 操作数直接加入后缀表达式
            postfix += c;
        }
        else if (c == '(') { // 左括号入栈
            opStack.push(c);
        }
        else if (c == ')') { // 右括号，弹出栈中元素直到左括号
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty() && opStack.top() == '(') {
                opStack.pop(); // 弹出左括号
            }
        }
        else if (isOperator(c)) { // 运算符
/* 在把当前运算符 c 压入栈之前，必须先处理 opStack 中已有的、优先级更高或相等的运算符*/
            while (!opStack.empty() && opStack.top() != '(' && getPriority(opStack.top()) >= getPriority(c)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        }
    }

    // 弹出栈中剩余的运算符
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }

    return postfix;
}

// 计算后缀表达式的值
int calculatePostfix(const string& postfix) {
    stack<int> numStack;

    for (char c : postfix) {
        if (isdigit(c)) { // 操作数入栈，字符转整数
            numStack.push(c - '0');
        }
        else if (isOperator(c)) { // 运算符，弹出两个操作数计算
            int right = numStack.top();
            numStack.pop();
            int left = numStack.top();
            numStack.pop();

            switch (c) {
            case '+':
                numStack.push(left + right);
                break;
            case '-':
                numStack.push(left - right);
                break;
            case '*':
                numStack.push(left * right);
                break;
            case '/':
                numStack.push(left / right);
                break;
            }
        }
    }

    return numStack.top(); // 最终结果
}

int main() {
    string infix;
    cout << "请输入四则运算表达式（操作数为一位整数）：";
    getline(cin, infix);

    string postfix = infixToPostfix(infix);
    int result = calculatePostfix(postfix);

    cout << "计算结果：" << result << endl;

    return 0;
}
//3 * (7 - 2 * 2) + 8 / 4