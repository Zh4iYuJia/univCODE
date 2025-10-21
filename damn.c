#include <stdio.h>
#include <string.h>

int isCircular(int n, int m) {
    char str_n[20], str_m[20];
    sprintf(str_n, "%d", n);
    sprintf(str_m, "%d", m);

    // 如果长度不同，直接返回 false
    if (strlen(str_n) != strlen(str_m)) return 0;

    // 生成循环数
    char double_str_n[40]; // 存放 n 的拼接字符串
    strcpy(double_str_n, str_n);
    strcat(double_str_n, str_n); // 拼接字符串 n + n

    // 检查 m 是否在拼接后的字符串中
    return strstr(double_str_n, str_m) != NULL;
}

int main() {
    int A, B;
    scanf("%d %d", &A, &B);

    int count = 0;

    for (int n = A; n <= B; n++) {
        for (int m = n + 1; m <= B; m++) {
            if (isCircular(n, m)) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}
