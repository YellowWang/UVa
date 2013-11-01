// uva10344 排列+回溯
// 几乎没有剪枝和优化，所以低空飘过

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;

#define len 5
int d[len];
int g_p[len];
// 遍历符号
bool search_symbol(int cur, int n, int* p, int* newd);
// 遍历数字
bool search_num(int idx, int num, int max, int* visit, int* p);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    while (scanf("%d %d %d %d %d", &d[0], &d[1], &d[2], &d[3], &d[4]) && d[0])
    {
        int visit[5];
        memset(visit, 0, sizeof(visit));

        bool possible = search_num(0, 5, 5, visit, g_p);
        if (possible)
            printf("Possible\n");
        else
            printf("Impossible\n");
    }

    return 0;
}

bool search_num(int idx, int num, int max, int* visit, int* p)
{
    if (idx == num)
    {
        int newd[5];
        for (int i = 0; i < num; i++)
        {
            newd[i] = d[p[i]];
        }
        int newp[5];
        return search_symbol(0, 4, newp, newd);
    }
    for (int i = 0; i < max; i++)
    {
        if (!visit[i])
        {
            p[idx] = i;
            visit[i] = 1;
            if (search_num(idx+1, num, max, visit, p))
                return true;
            visit[i] = 0;
        }
    }
    return false;
}

bool search_symbol(int cur, int n, int* p, int* newd)
{
    if (cur == n)
    {
        int sum = newd[0];
        for (int i = 1; i <= n; i++)
        {
            if (p[i-1]==0)
                sum += newd[i];
            else if (p[i-1]==1)
                sum -= newd[i];
            else
                sum *= newd[i];
        }
        return sum == 23;
    }

    for (int k = 0; k < 3; k++)
    {
        p[cur] = k;
        if (search_symbol(cur+1, n, p, newd))
            return true;
    }

    return false;
}