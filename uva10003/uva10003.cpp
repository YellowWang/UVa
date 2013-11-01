// uva10003 dp
// 重点：优化记忆方式。从1000^2降到50^2。
// 参考：http://blog.csdn.net/biran007/article/details/3865350
 
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
 
#define int_max 9999999
#define len 52
int g_cuts[len];
int f[len][len];
int stick_len, num;
int dp(int start, int end);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    while (scanf("%d %d", &stick_len, &num) && stick_len)
    {
        for (int i = 1; i <= num; i++)
        {
            scanf("%d", &g_cuts[i]);
        }
        memset(f, -1, sizeof(f));
 
        // 重点：将stick的两个端点，设置为两个cut。这样就把stick的长度降为50级别。
        g_cuts[0] = 0;
        g_cuts[num+1] = stick_len;
 
        printf("The minimum cutting is %d.\n", dp(0, num+1));
    }
 
    return 0;
}
 
int dp(int start, int end)
{
    // 之间没有cut了
    if (start + 1 == end)
        return 0;
 
    // 记忆
    if (f[start][end] >= 0)
        return f[start][end];
 
    int min_price = g_cuts[end]-g_cuts[start];
    int t = int_max;
    // 遍历找到最小的price
    for (int i = start+1; i < end; i++)
    {
        int t1 = dp(start, i);
        int t2 = dp(i, end);
        t = min(t, t1+t2);
    }
 
    f[start][end] = min_price + t;
    return min_price + t;
}