// uva10465 dp
// 完全背包问题变形。
 
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
 
#define time_len 10001
int f[time_len];
#define burger_len 2
int burger[burger_len];
int g_time;
void dp();
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    while (scanf("%d %d %d", &burger[0], &burger[1], &g_time)!=EOF)
    {
        dp();
    }
 
    return 0;
}
 
void dp()
{
    memset(f, -1, sizeof(int)*(g_time+1));
 
    f[0]=0;
    for (int i = 0; i < burger_len; i++)
    {
        for (int k = burger[i]; k < g_time+1; k++)
        {
             int t = k-burger[i];
            if (f[t] >= 0)
            {
                f[k] = max(f[k], f[t] + 1);
            }
        }
    }
 
    for (int i = g_time; i >= 0; i--)
    {
        if (f[i] >= 0)
        {
            printf("%d", f[i]);
            if (i!=g_time)
                printf(" %d", g_time-i);
            printf("\n");
            break;
        }
    }
}