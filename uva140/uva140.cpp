// uva140 带宽问题 排列、回溯
// 

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;

#define len 256
int g[len][len]; //两点之间是否通路
int mLetter[len]; //根据字母（点）得到排列中的位置
char d[len]; //每个点的位置
int visit[len]; 

int g_min_list[len];// 最小的排列
int g_min; // 最小带宽

// 解析输入字符串
int parse(char* p);
// 排列
void permutation(int n, int* visit, int cur, int bandwidth);


int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    char str[512];
    while (gets(str) && str[0]!='#')
    {
        // 解析数据
        memset(g, 0, sizeof(g));
        int n = parse(str);

        // 排列
        memset(visit, 0, sizeof(visit));
        memset(mLetter, 0, sizeof(mLetter));
        g_min = n;
        permutation(n, visit, 0, 0);

        // 输出
        for (int i = 0; i < n; i++)
        {
            printf("%c ", d[g_min_list[i]]);
        }
        printf("-> %d\n", g_min);
    }

    return 0;
}

int parse(char* p)
{
    memset(d, 0, sizeof(d));
    int vis[len];
    memset(vis, 0, sizeof(vis));
    int idx=0;

    char node;
    int state = 0;
    while (*p)
    {
        if (*p == ':')
        {
            state = 1;
            p++;
            continue;
        }
        if (*p == ';')
        {
            state = 0;
            p++;
            continue;
        }

        if (state == 0)
        {
            node=(*p);
            if (!vis[*p])
            {
                vis[*p]=1;
                d[idx++]=*p;
            }
        }
        else if (state == 1)
        {
            if (!vis[*p])
            {
                vis[*p]=1;
                d[idx++]=*p;
            }
            g[node][*p]=1;
            g[*p][node]=1;
        }
        p++;
    }

    return idx;
}

// 计算带宽，p为排列的索引
int calc_bandwidth(int n, int* p)
{
    int bandwidth = 0;
    for (int i = 0; i < n; i++)
    {
        int node1 = d[p[i]];
        for (int k = 0; k < n; k++)
        {
            if (g[node1][d[p[k]]])
            {
                bandwidth = max(bandwidth, abs(mLetter[d[p[k]]]-i));
                if (bandwidth == n-1)
                    return n-1;
            }
        }
    }
    return bandwidth;
}

void permutation(int n, int* visit, int cur, int bandwidth)
{
    // 剪枝：如果某一个扩展，发现带宽已经超过最小值，那么就剪掉
     if (bandwidth > g_min)
          return;
    if (cur == n)
    {
        if (bandwidth < g_min)
        {
            g_min = bandwidth;
            memcpy(g_min_list, visit, sizeof(int)*n);
        }
        // 如果带宽相同，那么优先排列的字母序
        else if (bandwidth == g_min)
        {
            for (int i = 0; i < n; i++)
            {
                if (d[g_min_list[i]] > d[visit[i]])
                {
                    memcpy(g_min_list, visit, sizeof(int)*n);
                    return;
                }
                else if (d[g_min_list[i]] < d[visit[i]])
                {
                    break;
                }
            }
        }
        return;
    }

    int i,j;
    for (i = 0; i < n; i++)
    {
        int ok = 1;
        for (j = 0; j < cur; j++)
        {
            if (visit[j] == i)
                ok = 0;
        }
        if (ok)
        {
            visit[cur] = i;
            mLetter[d[i]] = cur;
            if (cur)
                permutation(n , visit, cur+1, calc_bandwidth(cur+1, visit));
            else
                permutation(n , visit, cur+1, 0);
        }
    }
}