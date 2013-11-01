// uva208 ���ݡ���֦
// ����֦��ֱ�ӳ�ʱ��
// ��֦���Ѳ����յ����ڵ���ͨͼ������
// ������֦�뷨���Ѿ��߹��Ľڵ��·�߱������������´��ֱ���������ڵ��ʱ�򣬾�ֱ���ñ����·�ߣ���Ҫ�ж�һ���Ƿ��֮ǰ�ڵ��ظ�����

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;

#define len 21
int g[len][len];
int visit[len];
int connect[len]; // ���յ���ͨ����ôΪ1
int res[len];
int g_max;
// ��֦
void dfs_connect(int cur, int n);
// ����
void search(int cur, int idx, int n, int fire);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int cases = 1;
    int fire;
    while (scanf("%d", &fire)!=EOF)
    {
        memset(g, 0, sizeof(g));
        memset(visit, 0, sizeof(visit));
        memset(connect, 0, sizeof(connect));
        g_max = 0;

        int x,y;
        int max_corner=0;
        while (scanf("%d %d", &x, &y) && x)
        {
            g[x][y]=1;
            g[y][x]=1;
            max_corner = max(max_corner, max(x, y));
        }

        dfs_connect(fire, max_corner);

        printf("CASE %d:\n", cases++);
        search(0, 1, max_corner, fire);
        printf("There are %d routes from the firestation to streetcorner %d.\n", g_max, fire);
    }

    return 0;
}

void dfs_connect(int cur, int n)
{
    connect[cur]=1;
    for (int i = 1; i <= n; i++)
    {
        if (!connect[i] && g[cur][i])
        {
            dfs_connect(i, n);
        }
    }
}

void search(int cur, int idx, int n, int fire)
{
    if (idx == fire)
    {
        for (int i = 0; i < cur; i++)
        {
            if (res[i])
                printf("%d ", res[i]);
        }
        printf("%d\n", fire);
        g_max++;
        return;
    }
    if (cur == n)
        return;

    visit[idx] = 1;
    res[cur] = idx;
    for (int i = 1; i <= n; i++)
    {
        if (!visit[i] && g[idx][i] && connect[i])
        {
            search(cur+1, i, n, fire);
        }
    }
    visit[idx] = 0;
}