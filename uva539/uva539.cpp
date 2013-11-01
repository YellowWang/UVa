// uva539 图 边的遍历
// 注意边不能重复走

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;

#define len 26

int g[len][len];
int visit[len][len];
int g_layers;
void dfs(int idx, int num, int layers);


int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int nodes, edges;
    while (scanf("%d %d", &nodes, &edges) && nodes)
    {
        memset(g, 0, sizeof(g));
        memset(visit, 0, sizeof(visit));
        g_layers = 0;

        int x,y;
        for (int i = 0; i < edges; i++)
        {
            scanf("%d %d", &x, &y);
            g[x][y]=1;
            g[y][x]=1;
        }

        for (int i = 0; i < nodes; i++)
        {
            dfs(i, nodes, 0);
        }

        printf("%d\n", g_layers);
    }

    return 0;
}

void dfs(int idx, int num, int layers)
{

    for (int i = 0; i < num; i++)
    {
        if (!visit[idx][i] && g[idx][i])
        {
            visit[idx][i]=1;
            visit[i][idx]=1;

            dfs(i, num, layers+1);

            visit[idx][i]=0;
            visit[i][idx]=0;
        }
    }

    g_layers = max(g_layers, layers);
}