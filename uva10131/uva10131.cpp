// uva10131 dp
// 先按照重量升序排序，然后求iq的最长降序的子序列。
 
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
 
#define elp_len 1000
struct Node
{
    int weight;
    int iq;
    int idx;
};
Node g_n[elp_len];
int f[elp_len];
int road[elp_len];
void dp(int num);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int i = 0;
    while (scanf("%d %d", &g_n[i].weight, &g_n[i].iq)!=EOF)
    {
        g_n[i].idx = i;
        i++;
    }
 
    dp(i);
    return 0;
}
 
int comp(const void* a, const void* b)
{
    return ((Node*)a)->weight - ((Node*)b)->weight;
}
 
void dp(int num)
{
    qsort(g_n, num, sizeof(Node), comp);
 
    int max_s = 0;
    int max_i = 0;
    for (int i = 0; i < num; i++)
    {
        int s = 0;
        int pre_i = 0;
        for (int k = 0; k < i; k++)
        {
            if (g_n[i].iq < g_n[k].iq)
            {
                if (f[k] > s)
                {
                    s = f[k];
                    pre_i = k;
                }
            }
        }
        f[i] = s+1;
        road[i] = pre_i;
 
        if (f[i] > max_s)
        {
            max_s = f[i];
            max_i = i;
        }
    }
 
    // 输出
    printf("%d\n", max_s);
    int ti = max_i;
    deque<int> q;
    for (int i = 0; i < max_s; i++)
    {
        q.push_front(g_n[ti].idx);
        ti = road[ti];
    }
    for (int i = 0; i < max_s; i++)
    {
        printf("%d\n", q[i]+1);
    }
}