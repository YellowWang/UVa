// uva624 dp
// 0-1背包问题变形。和uva562很像，不过这个需要记录路径。
 
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
 
#define len 21
int g_n[len];
int minutes, num;
int f[10000];
int road[10000];
void dp();
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
 
    while (scanf("%d %d", &minutes, &num)!=EOF)
    {
        for (int i = 0; i < num; i++)
        {
            scanf("%d", &g_n[i]);
        }
 
        dp();
    }
 
    return 0;
}
 
void dp()
{
    memset(f, 0, sizeof(int)*(minutes+1));
    memset(road, -1, sizeof(int)*(minutes+1));
 
    f[0]=1;
    for (int i = 0; i < num; i++)
    {
        for (int k = minutes; k >= g_n[i]; k--)
        {
            if (!f[k])
            {
                f[k] = f[k - g_n[i]];
                road[k] = k - g_n[i];
            }
        }
    }
 
 
    // output
    int idx = 0, sum = 0;
    for (int k = minutes; k >= 0; k--)
    {
        if (f[k])
        {
            idx = k;
            sum = k;
            break;
        }
    }
 
    deque<int> q;
    while (idx >= 0)
    {
        q.push_front(idx);
        idx = road[idx];
    }
 
    for (int i = 1; i < q.size(); i++)
    {
        printf("%d ", q[i]-q[i-1]);
    }
    printf("sum:%d\n", sum);
}