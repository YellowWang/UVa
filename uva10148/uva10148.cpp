// uva10148 ̰��
// ����ѡ�����⡣���㷨���ž��䡷P154
// ÿ���߶ΰ����ұߵĵ���д�С��������Ȼ�󾡿���ѡ���ұߵĵ㡣
// �������ƣ�ֻ������������ܷ��ù���ƣ�ÿ���߶ζ���Ҫ��K������ƣ�����߶γ��Ȳ�������ôȫ���ݷù���ơ�

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
Bill g_bill; // ���Χ�߶Σ�ĳ�����й��Ϊ1.

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
            // ��ֹ����
             g_nodes[i].x1+=len;
             g_nodes[i].x2+=len;
            // ��С�ķŵ����
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

    // �߶��ұߵ��С��������
    qsort(g_nodes, N, sizeof(Node), comp);

    for (int i = 0; i < N; i++)
    {
        int billboards=0;
        // �ȼ�������߶εĹ������
        for (int k = g_nodes[i].x1; k <= g_nodes[i].x2; k++)
        {
            billboards += g_bill.bill[k]>0;
        }
        // �������K����ô���е�����
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