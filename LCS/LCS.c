#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

// ����LCS���
void lcsLength(char* x, char* y);
// �������C
void printC(int m, int n);
// �������B
void printB(int m, int n);
// �̲�ԭʼ�������������
void printLcsSingle(char* str, int i, int j);
// ������е�LCS
void printLcs(char* x, char* y, int m, int n);
// �ݹ�Ѱ��LCS
void findLcs(char* x, char* y, int xLen, int yLen, int i, int j, int remain, char* seq);

int** c;
char** b; // ��Ÿ�����ָ��

int main()
{
    char x[MAX_STRING_LENGTH], y[MAX_STRING_LENGTH];

    printf("���������ַ�����һ��һ��\n");
    gets_s(x, MAX_STRING_LENGTH);
    gets_s(y, MAX_STRING_LENGTH);

    lcsLength(x, y);

    printf("����C����\n");
    printC(strlen(x), strlen(y));
    printf("����B����\n");
    printB(strlen(x), strlen(y));
    printf("���е�LCS����\n");
    printLcs(x, y, strlen(x), strlen(y));

    system("pause");
    return 0;
}

void lcsLength(char* x, char* y)
{
    int m = strlen(x);
    int n = strlen(y); // ����ַ�������

    // ����c��b���飬������Ӧ�ĳ�ʼ��
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

    // ����x��y�Ĺ���������
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
    printf("�Ϸ�Ϊ1��˳ʱ������������Ͻ�Ϊ8\n");
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
    // ��ʼ������
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // Ѱ�ҿ�ʼ�й������еĵط�
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
    // ����ַ�
    if (remain == 0) {
        for (int k = c[xLen][yLen] - 1; k >= 0; k--) {
            putchar(seq[k]);
        }
        putchar('\n');
        return;
    }
    int j0 = j;
    int remain0 = remain; // �浵ԭʼ���ݣ����ڻ���
    for (; i <= xLen; i++) {
        for (j = j0; j <= yLen; j++) {
            remain = remain0;
            // ��ĳһ��λ���ҵ��������Ĺ����ַ�
            if ((c[i][j] == c[i - 1][j] + 1)
                && (c[i][j] == c[i][j - 1] + 1)
                && (c[i][j] == c[i - 1][j - 1] + 1)) {
                remain--; // ʣ��Ҫ�ҵ��ַ�����1
                seq[remain] = x[i - 1]; // ��������ַ�

                findLcs(x, y, xLen, yLen, i + 1, j + 1, remain, seq);

                seq[remain] = 0; // ����һ���ַ�
            }
        }
    }
}