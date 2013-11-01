// uva10596 图 欧拉通路
// 入度和出度必须一样

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
using namespace std;

#define len 201
int d[len];
int g[len][len];
int visit[len];
int node_num;

int dfs(int i);

int main()
{
    freopen("1.txt", "r", stdin);

    int road_num;
    while (scanf("%d %d", &node_num, &road_num)!=EOF)
    {
        memset(d, 0, sizeof(d));
        memset(g, 0, sizeof(g));
        memset(visit, 0, sizeof(visit));

        for (int i = 0; i < road_num; i++)
        {
            int n1,n2;
            scanf("%d %d", &n1, &n2);
            g[n1][n2] = 1;
            d[n1]++;
            d[n2]++;
        }

        bool err=false;
        for (int i = 0; i < node_num; i++)
        {
            if (d[i])
            {
                if (d[i] & 0x01)
                {
                    err = true;
                    break;
                }
            }
        }
        if (err)
        {
            printf("Not Possible\n");
            continue;
        }

        // 遍历所有节点
        if (node_num == dfs(0))
        {
            printf("Possible\n");
        }
        else
            printf("Not Possible\n");
    }
    return 0;
}

int dfs(int i)
{
    visit[i] = 1;

    int num = 1;
    for (int k = 0; k < node_num; k++)
    {
        if (!visit[k] && g[i][k])
        {
            num += dfs(k);
        }
    }
    return num;
}