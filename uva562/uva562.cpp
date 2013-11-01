// uva562 dp
// 背包问题变形。统计给其中一个人的钱数。f(i)是这个人是否可以有这个数目的钱。
// f(i) = f(i - g(j)); g(j)是第j个钱的币值（钱数）。
// 公式的意思是：如果现在的钱数-当前硬币的币值是可以有的钱数，那么现在的钱数也是可以有的。
// 可以有代表这个钱的数目是合法的。如果2个硬币1、5.那么4就不合法。
 
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
 
#define len 100
int g_n[len];
int f[50001];
void dp(int num, int total);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int cases;
    scanf("%d", &cases);
 
    while (cases--)
    {
        int num;
        scanf("%d", &num);
        int total = 0;
        for (int i = 0; i < num; i++)
        {
            scanf("%d", &g_n[i]);
            total += g_n[i];
        }
 
        dp(num, total);
    }
 
    return 0;
}
 
void dp(int num, int total)
{
    memset(f, 0, sizeof(int)*total);
 
    f[0] = 1;
    for (int i = 0; i < num; i++)
    {
        for (int k = total; k >= g_n[i]; k--)
        {
            if (!f[k])
                f[k] = f[k - g_n[i]];
        }
    }
 
    for (int i = (total>>1); i >= 0; i--)
    {
        if (f[i])
        {
            printf("%d\n", total - (i<<1));
            break;
        }
    }
}