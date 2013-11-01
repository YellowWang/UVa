// uva208 回溯、剪枝
// 不剪枝，直接超时。
// 剪枝：把不和终点所在的连通图剪掉。
// 其它剪枝想法：已经走过的节点的路线保存起来，当下次又遍历到这个节点的时候，就直接用保存的路线（需要判断一下是否和之前节点重复）。

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
int connect[len]; // 和终点连通，那么为1
int res[len];
int g_max;
// 剪枝
void dfs_connect(int cur, int n);
// 回溯
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