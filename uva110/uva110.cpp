// uva110 特殊规则排列
// 首先特殊规则排列，每次需要移动元素。其次是生成pascal代码，这个格式可要考虑的多，有点蛋疼。

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

#define  len 9
char g_data[len];

//用于输出
void begin(int n);
void end();
//枚举排列，并处理格式
void permutation(int n, int cur, char* p);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        for (int i = 0; i < len; i++)
        {
            g_data[i] = 'a'+i;
        }

        int n;
        scanf("%d", &n);

        begin(n);
        permutation(n, 0, g_data);
        end();

        if (cases != 0)
            printf("\n");
    }

    return 0;
}

void begin(int n)
{
    printf("program sort(input,output);\nvar\n");
    for (int i = 0; i < n; i++)
    {
        printf("%c", 'a'+i);
        if (i != n-1)
            printf(",");
    }
    printf(" : integer;\n");
    printf("begin\n");
    printf("  readln(");
    for (int i = 0; i < n; i++)
    {
        printf("%c", 'a'+i);
        if (i != n-1)
            printf(",");
    }
    printf(");\n");

}

void end()
{
    printf("  end.\n");
}

void fmt_blank(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

void permutation(int n, int cur, char* p)
{
    if (cur + 1 == n)
    {
        p[n]=0;
        fmt_blank((cur+1)<<1);
        printf("writeln(");
        for (int i = 0; i < n; i++)
        {
            printf("%c", p[i]);
            if (i != n-1)
                printf(",");
        }
        printf(")\n");
        return;
    }


    fmt_blank((cur+1)<<1);
    printf("if %c < %c then\n", p[cur], p[cur+1]);

    permutation(n, cur+1, p);

    for (int i = cur; i >= 0; i--)
    {
        fmt_blank((cur+1)<<1);

        //移动元素
        int t = p[i];
        p[i] = p[i+1];
        p[i+1] = t;

        if (i > 0)
        {
            printf("else if %c < %c then\n", p[i-1], p[i]);
        }
        else
        {
            printf("else\n");
        }

        permutation(n, cur+1, p);
    }

    // 还原格式
    for (int i = 0; i <= cur; i++)
    {
        int t = p[i];
        p[i] = p[i+1];
        p[i+1] = t;
    }
}