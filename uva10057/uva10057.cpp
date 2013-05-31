// uva10057 贪心
// 中位数，各种细节
// 从小到大排序，如果是奇数，那么中间的就是中位数。如果是偶数，那么中间的两个数的闭区间，也都是中位数。

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

#define len 1000000
int g_n[len];
int comp(const void* a, const void* b)
{
    return *((int*)a) - *((int*)b);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int num;
    while (scanf("%d", &num)!=EOF)
    {
        for (int i = 0; i < num; i++)
            scanf("%d", &g_n[i]);

        if (num == 1)
        {
            printf("%d 1 1\n", g_n[0]);
            continue;
        }

        qsort(g_n, num, sizeof(int), comp);

        int mid_idx = 0;
        if (num & 0x01)
        {
            mid_idx = num>>1;
            int A = g_n[mid_idx];
            int sameOfA = 0;
            int same_idx = mid_idx;
            while (g_n[same_idx] == g_n[mid_idx] && same_idx >= 0)
                sameOfA++,same_idx--;
            same_idx = mid_idx+1;
            while (g_n[same_idx] == g_n[mid_idx] && same_idx < num)
                sameOfA++,same_idx++;
            printf("%d %d 1\n", A, sameOfA);
        }
        else
        {
            mid_idx = (num>>1)-1;
            int A = g_n[mid_idx];
            int sameOfA = 0;
            int same_idx = mid_idx;
            while (g_n[same_idx] == g_n[mid_idx] && same_idx >= 0)
                sameOfA++,same_idx--;
            same_idx = mid_idx+1;
            while (g_n[same_idx] == g_n[mid_idx+1] && same_idx < num)
                sameOfA++,same_idx++;
            printf("%d %d %d\n", A, sameOfA, g_n[mid_idx+1]-g_n[mid_idx]+1);
        }
    }

    return 0;
}