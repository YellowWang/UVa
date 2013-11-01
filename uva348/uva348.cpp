// uva348 dp
// 矩阵连乘。参考《算法竞赛入门》（刘汝佳）9.4.1
// 本题特点是要保存路径和可视化输出。
 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <queue> 
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;
 
#define len 11
// 代表一个矩阵
struct Node
{
    int a,b;
    Node()
    {
        a =0; b = 0;
    }
    Node(int a, int b)
    {
        this->a = a;
        this->b = b;
    }
};
// 输入矩阵
Node g_n[len];
// f(i,j)代表从第i个矩阵到第j个矩阵的最小计算量
int f[len][len];
// f_n(i,j)代表从第i个矩阵到第j个矩阵的最小计算量后的结果矩阵
Node f_n[len][len];
// road(i,j)代表从第i个矩阵到第j个矩阵的最后一个结合点
int road[len][len];
int num;
void dp(int start, int end);
void output(int start, int end);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int cases = 1;
    while (scanf("%d", &num) && num)
    {
        for (int i = 0; i < num; i++)
        {
            scanf("%d %d", &g_n[i].a, &g_n[i].b);
        }
 
        memset(f, 0, sizeof(f));
        memset(road, -1, sizeof(road));
        memset(f_n, 0, sizeof(f_n));
 
        dp(0, num-1);
 
        printf("Case %d: ", cases);
        output(0, num-1);
        printf("\n");
 
        cases++;
    }
 
    return 0;
}
 
// 递归进行可视化输出
void output(int start, int end)
{
    if (start == end)
    {
        printf("A%d", start+1);
        return;
    }
    printf("(");
    int m = road[start][end];
    output(start, m);
    printf(" x ");
    output(m+1, end);
    printf(")");
}
 
void dp(int start, int end)
{
    if (f[start][end])
        return;
 
    if (start == end)
    {
        f_n[start][end] = g_n[start];
        return;
    }
    if (start + 1 == end)
    {
        f[start][end]=g_n[start].a * g_n[start].b * g_n[end].b;
        road[start][end] = start;
        f_n[start][end] = Node(g_n[start].a, g_n[end].b);
        return;
    }
 
    int t = 0;
    int min_t = 999999999;
    int min_i = 0;
    Node min_n;
    for (int i = start; i < end; i++)
    {
        t = 0;
        dp(start, i);
        t += f[start][i];
        dp(i+1, end);
        t += f[i+1][end];
 
        Node &n1 = f_n[start][i];
        Node &n2 = f_n[i+1][end];
        t += n1.a * n1.b * n2.b;
        if (t < min_t)
        {
            min_t = t;
            min_n = Node(n1.a, n2.b);
            min_i = i;
        }
    }
    f[start][end] = min_t;
    road[start][end] = min_i;
    f_n[start][end] = min_n;
    return;
}