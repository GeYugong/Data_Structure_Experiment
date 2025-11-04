#include <iostream>
#include <string>
using namespace std;


int find_last_occurrence(const string& str, const string& substr) {
    int str_len = str.length();
    int substr_len = substr.length();

    // 基本情况处理：如果子串比主串还长，或者子串为空，则无法匹配。
    if (substr_len > str_len || substr_len == 0) {
        return -1;
    }

    // 从右向左遍历主串中所有可能的起始位置
    // 最后一个可能的起始位置是 str_len - substr_len
    for (int i = str_len - substr_len; i >= 0; --i) {
        bool is_match = true;

        // 对于当前的起始位置i，比较 str[i...i+substr_len-1] 与 substr
        for (int j = 0; j < substr_len; ++j) {
            // 如果在任何一点发生失配，则当前起始位置i不匹配 [cite: 222]
            if (str[i + j] != substr[j]) {
                is_match = false;
                break; // 中断内层循环，继续检查下一个起始位置
            }
        }

        // 如果内层循环正常完成（is_match 仍为 true），说明找到了一个完整的匹配 
        // 因为我们是从右向左搜索的，所以第一个找到的匹配就是最后一个匹配
        if (is_match) {
            return i; // 立即返回当前位置
        }
    }

    // 如果主循环结束仍未返回，说明没有找到任何匹配项
    return -1;
}

int main() {
    string str;
    string substr;

    cout << "请输入主串str：" << endl;
    cin >> str;

    cout << "请输入子串substr：" << endl;
    cin >> substr;

    int position = find_last_occurrence(str, substr);

    if (position != -1) {
        cout << "子串 \"" << substr << "\" 在主串 \"" << str << "\" 中最后一次出现的位置是：" << position << endl;
    }
    else {
        cout << "在主串 \"" << str << "\" 中未找到子串 \"" << substr << "\"。" << endl;
    }

    return 0;
}