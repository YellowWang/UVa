// uva10130 dp
// 经典0-1背包问题，用滚动数组实现，注释部分为普通实现。

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

#define len 1001
#define total_len 31
struct Node
{
    int price;
    int weight;
};
Node g_n[len];
int num, total;
int f[total_len];
void dp();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    g_n[0].price = g_n[0].weight = 0;

    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        scanf("%d", &num);
        total = 0;
        for (int i = 1; i <= num; i++)
        {
            scanf("%d %d", &g_n[i].price, &g_n[i].weight);
            total += g_n[i].weight;
        }

        dp();

        int people_num;
        scanf("%d", &people_num);
        int price_sum = 0;
        for (int i = 0; i < people_num; i++)
        {
            int weight;
            scanf("%d", &weight);
            price_sum += f[weight];
        }
        printf("%d\n", price_sum);
    }

    return 0;
}

// 滚动数组
void dp()
{
    memset(f, 0, sizeof(f));

    for (int i = 1; i <= num; i++)
    {
        for (int k = total_len-1; k >= 0; k--)
        {
            if (k >= g_n[i].weight)
            {
                int t = f[k-g_n[i].weight]+g_n[i].price;
                f[k] = max(f[k], t);
            }
        }
    }
}

/*
// 普通的dp
void dp()
{
    memset(f, 0, sizeof(f));

    for (int i = 1; i <= num; i++)
    {
        for (int k = 1; k < total_len; k++)
        {
            f[k][i] = f[k][i-1];
            if (k >= g_n[i].weight)
            {
                int t = f[k-g_n[i].weight][i-1]+g_n[i].price;
                f[k][i] = max(f[k][i], t);
            }
        }
    }
}
*/