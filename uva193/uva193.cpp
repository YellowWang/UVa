// uva193 ����
// ��ɫ����

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;

#define len 101
int g[len][len];
int visit[len];

// ������
int g_max;
int g_visit[len];

// ����
void search(int cur, int n, int blacks);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    freopen("2.txt","w",stdout);
#endif

    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        memset(g, 0, sizeof(g));
        memset(visit, 0, sizeof(visit));
        g_max = 0;

        int num,edges;
        scanf("%d %d", &num, &edges);
        for (int i = 0; i < edges; i++)
        {
            int x,y;
            scanf("%d %d", &x, &y);
            g[x][y]=1;
            g[y][x]=1;
        }

        search(1, num, 0);

        // ��ʽ�����
        printf("%d\n", g_max);
        vector<int> v;
        for (int i = 1; i <= num; i++)
        {
            if (g_visit[i] == 2)
            {
                v.push_back(i);
            }
        }
        printf("%d", v[0]);
        for (int i = 1; i < v.size(); i++)
        {
            printf(" %d", v[i]);
        }
        printf("\n");
    }

    return 0;
}

// 1 �� 2��
void search(int cur, int n, int blacks)
{
    if (cur == n+1)
    {
        if (g_max < blacks)
        {
            g_max = blacks;
            memcpy(g_visit, visit, sizeof(g_visit));
        }

        return;
    }

     bool b = false;
    // �����Χ�нڵ㣬�����к�ɫ�ģ���ô�˵�ֻ���ǰ�ɫ��
     for (int i = 1; i <= n; i++)
     {
         if (g[cur][i] && visit[i] == 2)
         {
             visit[cur] = 1;
             search(cur+1, n, blacks);
             b = true;
             break;
         }
     }

     if (!b)
     {
        visit[cur] = 1;
        search(cur+1, n, blacks);
        visit[cur] = 2;
        search(cur+1, n, blacks+1);
        visit[cur] = 0;
    }

}