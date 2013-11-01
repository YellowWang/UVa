// uva167 回溯 八皇后变种
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


#define len 8
int g_d[len][len];
int sum[len];
int visit[len][len];
int max_sum;
void   search(int rows);


int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        for (int i = 0; i < len; i++)
        {
            for (int k = 0; k < len; k++)
            {
                scanf("%d", &g_d[i][k]);
            }
        }

        memset(sum, 0, sizeof(sum));
        memset(visit, 0, sizeof(visit));
        max_sum = 0;

        search(0);
        printf("%5d\n", max_sum);
    }

    return 0;
}

void   search(int rows)
{
    if (rows == len)
    {
        int s = 0;
        for (int i = 0; i < len; i++)
        {
            s += sum[i];
        }
        max_sum = max(max_sum, s);
        return;
    }

    for (int k = 0; k < len; k++)
    {
        if (visit[rows][k])
            continue;

        // 判断竖线
        bool can_move=true;
        for (int i = 0; i < len; i++)
        {
            if (visit[i][k])
            {
                can_move = false;
                break;
            }
        }
        if (!can_move)
            continue;

        // main diag
        int ii = rows;
        int kk = k;
        while (ii>=0 && kk>=0)
        {
            if (visit[ii][kk])
            {
                can_move = false;
                break;
            }
            ii--;
            kk--;
        }
        if (!can_move)
            continue;
        ii = rows;
        kk = k;
        while (ii < len && kk < len)
        {
            if (visit[ii][kk])
            {
                can_move = false;
                break;
            }
            ii++;
            kk++;
        }
        if (!can_move)
            continue;

        // side diag
        ii = rows;
        kk = k;
        while (ii>=0 && kk < len)
        {
            if (visit[ii][kk])
            {
                can_move = false;
                break;
            }
            ii--;
            kk++;
        }
        if (!can_move)
            continue;
        ii = rows;
        kk = k;
        while (ii < len && kk>=0)
        {
            if (visit[ii][kk])
            {
                can_move = false;
                break;
            }
            ii++;
            kk--;
        }
        if (!can_move)
            continue;

        visit[rows][k] = 1;
        sum[rows] = g_d[rows][k];
        search(rows+1);
        visit[rows][k] = 0;

    }
}