// uva 10004
// 开始想着找到环，环内节点数是基数就是错的。这条不归路走了很久，然后实在想不出好办法
// 最后用dfs，每个节点保存是否遍历过、颜色两个状态，就轻松过了。

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
using namespace std;

#define len 201
int g[len][len];
int d[len];
int pre[len];
int num;
int dd[len][2];

bool bfs(int node);
bool dfs(int node);
bool dfs2(int node, int color);
int main()
{
    //freopen("1.txt", "r", stdin);

    while (scanf("%d", &num)!=EOF && num)
    {
        memset(g, 0, sizeof(g));
        memset(d, 0, sizeof(d));
        memset(pre, -1, sizeof(pre));
        memset(dd, 0, sizeof(dd));

        int edge;
        scanf("%d", &edge);
        for (int i = 0; i < edge; i++)
        {
            int n1,n2;
            scanf("%d %d", &n1, &n2);
            g[n1][n2] = 1;
            g[n2][n1] = 1;
        }

        if (!dfs2(0, 0))
        {
            printf("NOT BICOLORABLE.\n");
        }
        else
            printf("BICOLORABLE.\n");

    }
    return 0;
}


bool dfs2(int node, int color)
{
    dd[node][color] = 1;
    int newcolor = 1-color;
    for (int i = 0; i < num; i++)
    {
        if (g[node][i] && !dd[i][newcolor])
        {
            if (dd[i][color] == 1)
            {
                return false;
            }
            else
            {
                if (!dfs2(i,newcolor))
                    return false;
            }
        }
    }
    return true;
}

bool dfs(int node)
{
    d[node] = 1;
    for (int i = 0; i < num; i++)
    {
        if (g[node][i] && i != pre[node])
        {
            // cycle
            if (d[i])
            {
                int node_num = 1;
                int p = node;
                while (pre[p]!=-1)
                {
                    p = pre[p];
                    ++node_num;
                }
                if (node_num & 0x01)
                    return false;
            }
            else
            {
                //d[node] = 1;
                pre[i] = node;
                if (!dfs(i))
                    return false;
                //d[node] = 0;
            }
        }
    }

    return true;
}

bool bfs(int node)
{
    deque<int> q;
    q.push_back(node);
    while (!q.empty())
    {
        int n = q.front();

        d[n] = 1;
        for (int i = 0; i < num; i++)
        {
            if (g[n][i])
            {
                // cycle
                if (d[i])
                {
                    int node_num = 1;
                    int p = n;
                    while (pre[p]!=-1)
                    {
                        p = pre[p];
                        ++node_num;
                    }
                    if (node_num & 0x01)
                        return false;
                }
                else
                {
                    pre[i] = n;
                    q.push_back(i);
                }
            }
        }

        q.pop_front();
    }
    return true;
}