// uva10474 ���򡢲�ѯ
// �ó������+���ַ����ض���ʱ������Ҫ�������⣬��д���ʺϵķ�����

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

#define len 10001
int g_d[len];
int g_sum[len]; //�ۼ�
int g_count[len]; //����

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int num, query;
    int cases = 1;
    while (scanf("%d %d", &num, &query) && num)
    {
        for (int i = 0; i < len; i++)
        {
            g_count[i]=0;
            g_sum[i]=0;
        }

        for (int i = 0; i < num; i++)
        {
            scanf("%d", &g_d[i]);
            g_count[g_d[i]]++;
        }

        g_sum[0] = g_count[0];
        for (int i = 1; i < len; i++)
        {
            g_sum[i] += g_sum[i-1] + g_count[i];
        }

        printf("CASE# %d:\n", cases++);
        for (int i = 0; i < query; i++)
        {
            int que;
            scanf("%d", &que);

            if (g_count[que] > 0)
                printf("%d found at %d\n", que, g_sum[que-1]+1);
            else
                printf("%d not found\n", que);
        }
    }

    return 0;
}