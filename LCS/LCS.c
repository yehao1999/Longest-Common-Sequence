#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

// 计算LCS表格
void lcsLength(char* x, char* y);
// 输出数组C
void printC(int m, int n);
// 输出数组B
void printB(int m, int n);
// 教材原始的输出单个序列
void printLcsSingle(char* str, int i, int j);
// 输出所有的LCS
void printLcs(char* x, char* y, int m, int n);
// 递归寻找LCS
void findLcs(char* x, char* y, int xLen, int yLen, int i, int j, int remain, char* seq);

int** c;
char** b; // 存放个数和指向

int main()
{
    char x[MAX_STRING_LENGTH], y[MAX_STRING_LENGTH];

    printf("输入两个字符串，一行一个\n");
    gets_s(x, MAX_STRING_LENGTH);
    gets_s(y, MAX_STRING_LENGTH);

    lcsLength(x, y);

    printf("数组C如下\n");
    printC(strlen(x), strlen(y));
    printf("数组B如下\n");
    printB(strlen(x), strlen(y));
    printf("所有的LCS如下\n");
    printLcs(x, y, strlen(x), strlen(y));

    system("pause");
    return 0;
}

void lcsLength(char* x, char* y)
{
    int m = strlen(x);
    int n = strlen(y); // 存放字符串长度

    // 创建c，b数组，并做相应的初始化
    c = (int**)malloc(sizeof(int*) * (m + 1));
    b = (char**)malloc(sizeof(char*) * (m + 1));
    for (int i = 0; i <= m; i++) {
        c[i] = (int*)malloc(sizeof(int) * (n + 1));
        b[i] = (char*)malloc(sizeof(char) * (n + 1));
        c[i][0] = 0;
        b[i][0] = ' ';
    }
    for (int j = 0; j <= n; j++) {
        c[0][j] = 0;
        b[0][j] = ' ';
    }

    // 处理x，y的公共子序列
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '8';
            }
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = '1';
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = '7';
            }
        }
    }
}

void printC(int m, int n)
{
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%d ", c[i][j]);
        }
        putchar('\n');
    }
}

void printB(int m, int n)
{
    printf("上方为1，顺时针递增，至左上角为8\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%c ", b[i][j]);
        }
        putchar('\n');
    }
}

void printLcsSingle(char* str, int i, int j)
{
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == '8') {
        printLcsSingle(str, i - 1, j - 1);
        putchar(str[i - 1]);
    }
    else if (b[i][j] == '1') {
        printLcsSingle(str, i - 1, j);
    }
    else {
        printLcsSingle(str, i, j - 1);
    }
}

void printLcs(char* x, char* y, int m, int n)
{
    // 初始化序列
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // 寻找开始有公共序列的地方
            if ((c[i][j] == 1)
                && (c[i][j - 1] == 0)
                && (c[i - 1][j] == 0)
                && (c[i - 1][j - 1] == 0)) {
                char lcsString[MAX_STRING_LENGTH] = { 0 };
                findLcs(x, y, m, n, i, j, c[m][n], lcsString);
            }
        }
    }
}

void findLcs(char* x, char* y, int xLen, int yLen, int i, int j, int remain, char* seq)
{
    // 输出字符
    if (remain == 0) {
        for (int k = c[xLen][yLen] - 1; k >= 0; k--) {
            putchar(seq[k]);
        }
        putchar('\n');
        return;
    }
    int j0 = j;
    int remain0 = remain; // 存档原始数据，用于回退
    for (; i <= xLen; i++) {
        for (j = j0; j <= yLen; j++) {
            remain = remain0;
            // 在某一个位置找到了新增的公共字符
            if ((c[i][j] == c[i - 1][j] + 1)
                && (c[i][j] == c[i][j - 1] + 1)
                && (c[i][j] == c[i - 1][j - 1] + 1)) {
                remain--; // 剩余要找的字符数减1
                seq[remain] = x[i - 1]; // 倒序放置字符

                findLcs(x, y, xLen, yLen, i + 1, j + 1, remain, seq);

                seq[remain] = 0; // 回退一格字符
            }
        }
    }
}