// uva10720 贪心
// 从高到低排序，如：4 3 3 1 1 1 1.然后取第一个数3，然后后面3个每个减去1.得：2 2 0 0 1 1.继续排序，如此往复。
// 如果减去1的时候为负数，那么就是impossible。

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
int g_n[len];
bool proc(int num);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int num;
    while (scanf("%d", &num) && num)
    {
        for (int i = 0; i < num; i++)
        {
            scanf("%d", &g_n[i]);
        }

        if (proc(num))
            printf("Possible\n");
        else
            printf("Not possible\n");
    }

    return 0;
}

int comp(const void* a, const void* b)
{
    return *((int*)b) - *((int*)a);
}

bool proc(int num)
{


    for (int i = 0; i < num; i++)
    {
        qsort(g_n, num, sizeof(int), comp);
        if (g_n[i])
        {
            int sz = i+1+g_n[i];
            if (sz > num)
                return false;
            for (int k = i+1; k < sz; k++)
            {
                if (g_n[k] == 0)
                    return false;
                g_n[k]--;
            }
        }
    }
    return true;
}