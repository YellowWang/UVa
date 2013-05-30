// uva10148 贪心
// 区间选点问题。《算法入门经典》P154
// 每个线段按照右边的点进行从小到大排序，然后尽可能选择右边的点。
// 本题限制：只有整数坐标才能放置广告牌；每个线段都需要有K个广告牌；如果线段长度不够，那么全部拜访广告牌。

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

#define len 10000
struct Bill
{
    char bill[len*2+1];
};
Bill g_bill; // 最大范围线段，某个点有广告为1.

#define node_len 1000
struct Node 
{
    int x1,x2;
};
Node g_nodes[node_len];
int v[len*2+1];
void proc(int K, int N);

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
        int K,N;
        scanf("%d %d", &K, &N);
        for (int i = 0; i < N; i++)
        {
            scanf("%d %d", &g_nodes[i].x1, &g_nodes[i].x2);
            // 防止负数
             g_nodes[i].x1+=len;
             g_nodes[i].x2+=len;
            // 把小的放到左边
            if (g_nodes[i].x1 > g_nodes[i].x2)
            {
                int t = g_nodes[i].x2;
                g_nodes[i].x2 = g_nodes[i].x1;
                g_nodes[i].x1 = t;
            }
        }

        proc(K, N);

        if (cases!=0)
            printf("\n");
    }

    return 0;
}

int comp(const void* a, const void* b)
{
    return ((Node*)a)->x2 - ((Node*)b)->x2;
}
int comp2(const void* a, const void* b)
{
    return *((int*)a) - *((int*)b);
}

void proc(int K, int N)
{
    memset(&g_bill, 0, sizeof(g_bill));
    int vi=0;

    // 线段右边点从小到大排序
    qsort(g_nodes, N, sizeof(Node), comp);

    for (int i = 0; i < N; i++)
    {
        int billboards=0;
        // 先计算这个线段的广告数量
        for (int k = g_nodes[i].x1; k <= g_nodes[i].x2; k++)
        {
            billboards += g_bill.bill[k]>0;
        }
        // 如果不足K，那么从有到左补齐
        if (billboards < K)
        {
            billboards = K-billboards;
            for (int k = g_nodes[i].x2; k >= g_nodes[i].x1 && billboards > 0; k--)
            {
                if (!g_bill.bill[k])
                {
                    billboards--;
                    g_bill.bill[k]=1;
                    v[vi++]=k;
                }
            }
        }
    }

    // ourtput
    qsort(v, vi, sizeof(int), comp2);
    printf("%d\n", vi);
    for (int i = 0; i < vi; i++)
    {
        printf("%d\n", v[i]-len);
    }
}