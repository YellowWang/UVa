// uva10706 二分
// 重在找到规律。
// 设d(n)为从1到n总共多少个数
// 设s(n)= d(1)+...+d(n)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

// 53000以上会超过int正向上限。
#define len 53000
unsigned int g_d[len];
unsigned int g_s[len];
void pre_proc();
int my_binary_searchs(int n);
int my_binary_searchd(int n);
int searchd(int i, int n);
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    freopen("2.txt","w",stdout);
#endif

    // 把s和d函数优先放到数组
    pre_proc();
    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        int n;
        scanf("%d", &n);

        // 首先找到在s函数的第几个
        int i = my_binary_searchs(n);
        // 得到一个单独的d函数的第几个
        n = n - g_s[i-1];
        // 找到在d函数的第几个
        i = my_binary_searchd(n);
        // 根据d函数的第几个，找到最后答案
        i = searchd(i, n);
        printf("%d\n", i);
    }

    return 0;
}

void pre_proc()
{
    g_d[0] = 0;
    g_s[0] = 0;
    for (int i = 1; i < 10; i++)
    {
        g_d[i] = g_d[i] + i;
        g_s[i] = g_s[i-1]+g_d[i];
    }
    for (int i = 10; i < 100; i++)
    {
        g_d[i] = g_d[i-1]+2;
        g_s[i] = g_s[i-1]+g_d[i];
    }
    for (int i = 100; i < 1000; i++)
    {
        g_d[i] = g_d[i-1]+3;
        g_s[i] = g_s[i-1]+g_d[i];
    }
    for (int i = 1000; i < 10000; i++)
    {
        g_d[i] = g_d[i-1]+4;
        g_s[i] = g_s[i-1]+g_d[i];
    }
    for (int i = 10000; i < len; i++)
    {
        g_d[i] = g_d[i-1]+5;
        g_s[i] = g_s[i-1]+g_d[i];
    }
}

int my_binary_searchs(int n)
{
    int l = 1, r = len;
    while (l < r)
    {
        int m = l + ((r-l)>>1);
        if (g_s[m] == n)
            return m;
        else if (g_s[m] > n)
            r = m;
        else
            l = m+1;
    }

    if (g_s[l] < n)
        l = l+1;
    return l;
}

int my_binary_searchd(int n)
{
    int l = 1, r = len;
    while (l < r)
    {
        int m = l + ((r-l)>>1);
        if (g_d[m] == n)
            return m;
        else if (g_d[m] > n)
            r = m;
        else
            l = m+1;
    }

    if (g_d[l] < n)
        l = l+1;
    return l;
}

int searchd(int i, int n)
{
    if (n == g_d[i])
        return i % 10;

    int d = n - g_d[i-1];

    deque<int> q;
    int t = i;
    while (t)
    {
        q.push_front(t%10);
        t = t / 10;
    }

    return q[d-1];
}