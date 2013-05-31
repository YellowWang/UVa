// uva10670 ̰��
// ��Ŀ������Ҫ������B�����ȫ��A��
// ��������ô�С�����������������ͬ��������ĸ����

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

#define len 100
struct Node
{
    char name[24];
    int cost;
};
Node g_nodes[len];
int comp(const void* a, const void* b)
{
    if (((Node*)a)->cost == ((Node*)b)->cost)
    {
        return strcmp(((Node*)a)->name, ((Node*)b)->name);
    }
    return ((Node*)a)->cost - ((Node*)b)->cost;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int cases;
    scanf("%d", &cases);
    for (int icase = 0; icase < cases; icase++)
    {
        int N,M,L;
        scanf("%d %d %d", &N, &M, &L);
        for (int i = 0; i < L; i++)
        {
            int cost = 0;
            int A,B;
            char str[64];
            scanf("%s", str);
            sscanf(str, "%[^:]:%d,%d", g_nodes[i].name, &A, &B);

            int n = N, selected_a = 0, selected_b = 0;
            while ((n>>1)>=M && B < A*(n>>1))
            {
                n = n>>1;
                // ����ѡ��B
                selected_b ++;
            }
            // ���ȫ��ѡ��A
            selected_a = n-M;
            // �������շ���
            g_nodes[i].cost = selected_a*A + selected_b*B;
        }

        // ����
        qsort(g_nodes, L, sizeof(Node), comp);

        // ���
        printf("Case %d\n", icase+1);
        for (int i = 0; i < L; i++)
        {
            printf("%s %d\n", g_nodes[i].name, g_nodes[i].cost);
        }
    }

    return 0;
}