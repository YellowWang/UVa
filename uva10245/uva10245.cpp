// uva10245 暴力 or 分治
// 二维上求距离最小的两个点
// 分治参考《算法导论》33.4章节
// 此代码是暴力剪枝

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

#define len 10000
struct Node
{
    double x,y;
};
Node g_n[len];
int comp(const void* a, const void* b)
{
    return ((Node*)a)->x > ((Node*)b)->x?1:-1;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int num;
    while (scanf("%d", &num) && num)
    {
        for (int i = 0; i < num; i++)
        {
            scanf("%lf %lf", &g_n[i].x, &g_n[i].y);
        }

        qsort(g_n, num, sizeof(Node), comp);

        double min_dis = 10000;
        for (int i = 0; i < num; i++)
        {
            for (int k = i+1; k < num; k++)
            {
                double d1 = g_n[k].x-g_n[i].x;
                double d2 = g_n[k].y-g_n[i].y;
                // 剪枝
                if (d1 >= min_dis)
                    break;
                double dis = sqrt(d1*d1+ d2*d2);
                if (dis < min_dis)
                    min_dis = dis;
            }
        }
        if (min_dis < 10000)
            printf("%.4lf\n", min_dis);
        else
            printf("INFINITY\n");
    }

    return 0;
}