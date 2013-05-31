// uva993 贪心
// 分解因子，优先从9到2.
// 题意：输入10，意思是一个自然数，每个位的乘积等于10，答案为25.
// 题目隐含条件，自然数每一位需要从小到大排序。

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

#define len 10
int g_n[len];
int proc(int num);
int comp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
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
        int sz = proc(num);
        if (sz)
        {
            qsort(g_n, sz, sizeof(int), comp);
            for (int i = 0; i < sz; i++)
            {
                printf("%d", g_n[i]);
            }
            printf("\n");
        }
        else
            printf("-1\n");
    }

    return 0;
}

int proc(int num)
{
    if (num == 1 || num == 0)
    {
        g_n[0] = num;
        return 1;
    }

    int mul_num = 0;
    int temp_num = num;
    while (mul_num < len && temp_num > 1)
    {
        bool found = false;
        for (int i = 9; i >= 2; i--)
        {
            if (temp_num % i == 0)
            {
                temp_num = temp_num/i;
                g_n[mul_num] = i;
                found = true;
                break;
            }
        }
        if (!found)
            return 0;
        mul_num++;
    }
    if (temp_num > 1)
        return 0;
    return mul_num;
}