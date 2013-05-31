// uva11100 ̰��
// ��ʼ�����һ�α��������Ծ������һ�ΰ�����������������ÿ���������������Ҫ��֤��С���������
// ����˼ά����ס������������ô��ôһ�α�����������������������һֱ������ˡ�
// ��ȷ�Ľ��������
// ���ҳ�����м���������ͨ����ͬ�ߴ���������ɵ�֪��
// Ȼ����ݳߴ�Ӵ�С���򣬲��ϵİ����Ž��⼸�������


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

int comp(const void* a, const void* b)
{
    return *((int*)b) - *((int*)a);
}

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
        // ����
        qsort(g_n, num, sizeof(int), comp);

        // �ҳ������ͬ������
        int t=g_n[0];
        int same_num = 1;
        int same_max = 1;
        for (int i = 1; i < num; i++)
        {
            if (t == g_n[i])
                same_num++;
            else
            {
                same_max = max(same_num, same_max);
                t= g_n[i];
                same_num = 1;
            }
        }
        same_max = max(same_num, same_max);
        printf("%d\n", same_max);

        // �����Ž�������
        vector<int> bags[len];
        int pos=0;
        for (int i = 0; i < num; i++)
        {
            bags[pos].push_back(g_n[i]);
            pos++;
            if (pos >= same_max)
                pos = 0;
        }

        // ���
        for (int i = 0; i < same_max; i++)
        {
            printf("%d", bags[i][0]);
            for (int k = 1; k < bags[i].size(); k++)
            {
                printf(" %d", bags[i][k]);
            }
            printf("\n");
        }

        printf("\n");
    }

    return 0;
}