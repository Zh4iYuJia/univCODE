#include <stdio.h>

int highestOrder(int x) {
    if (x == 0) return 1; // 处理零的情况
    int res = 1; 
    while (x >= 10) {
        res *= 10; // 简化乘法
        x /= 10;
    }
    return res; 
}

int main() {
    int A, B; 
    int ans = 0;
    scanf("%d %d", &A, &B);
    int order = highestOrder(A);

    for (int c = A; c <= B; c++) {
        int highestDigit = c / order; // 获取最高位数字
        int d = c; // 从 c 开始
        while (d <= B) {
            if (d > c) {
                ans++; // 统计大于 c 的有效数字
            }
            // 根据最高位更新 d
            d = (d % order) * 10 + highestDigit; // 生成新的 d
        }
    }

    printf("%d\n", ans);
    return 0; 
}
