#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

// 判断 n 和 m 是否为循环对
bool isCircular(int n, int m) {
    string str_n = to_string(n);
    string str_m = to_string(m);
    
    if (str_n.length() != str_m.length()) return false; // 长度不同，直接返回 false
    
    // 生成循环数
    string double_str_n = str_n + str_n; // 拼接字符串
    return double_str_n.find(str_m) != string::npos; // 检查 m 是否在拼接后的字符串中
}

int main() {
    int A, B;
    cin >> A >> B;

    int count = 0;

    for (int n = A; n <= B; n++) {
        for (int m = n+1; m <= B; m++) {
            if (isCircular(n, m)) {
                count++;
            }
        }
    }

    cout << count << endl;
    return 0;
}
