#include <stdio.h>

// 计算数字 x 的最高位数，例如 x = 12345 返回 10000
int getOrder(int num) {
    int order = 1; // 初始化最高位数
    while (num >= 10) {
        order *= 10; // 每次乘以 10，提升最高位
        num /= 10; // 除以 10，逐步缩小 num
    }
    return order; // 返回最高位数
}

int main() {
    int low, high; // 输入范围
    int count = 0; // 循环对计数器
    scanf("%d %d", &low, &high); // 读取输入的下界和上界
    
    // 遍历从下界到上界-1 的所有数字
    for (int n = low; n < high; n++) {
        int order = getOrder(n); // 获取当前数字的最高位数
        int t = n; // 初始化旋转数为当前数字

        do {
            // 生成下一个循环数
            t = (t % order) * 10 + (t / order);
            // 如果生成的旋转数在范围内且大于当前数字，则计数
            if (t > n && t <= high) {
                count++;
            }
        } while (t != n); // 直到旋转数回到最初的当前数字
    }

    printf("%d\n", count); // 输出循环对的数量
    return 0;
}

