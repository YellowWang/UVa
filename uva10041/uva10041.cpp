// uva10041 贪心
// 中位数，排序后中间的数

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

#define len 500
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

    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        int num;
        scanf("%d", &num);
        for (int i = 0; i < num; i++)
        {
            scanf("%d", &g_n[i]);
        }

        qsort(g_n, num, sizeof(int), comp);

        int mid_idx = num>>1;
        int sum = 0;
        for (int i = 0; i < num>>1; i++)
        {
            sum += g_n[mid_idx] - g_n[i];
        }
        for (int i = (num>>1)+1; i < num; i++)
        {
            sum += g_n[i] - g_n[mid_idx];
        }
        printf("%d\n", sum);
    }

    return 0;
}