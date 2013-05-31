// uva10382 贪心
// 最小覆盖问题变种
// 将园于矩形的交点映射到直线上，就是第n个洒水的线段范围。
// 最小覆盖问题可以参考uva10020

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

#define EPS 0.0000001f
#define len 10000
struct Node
{
    double x1, x2;
};
Node g_node[len];
double g_l,g_w;
int g_num;
double g_w2;
int g_selected_num;
bool proc();

int comp(const void* a, const void* b)
{
    return ((Node*)a)->x1 - ((Node*)b)->x1;
}

double get_distance(double r)
{
    return sqrt(r*r-g_w2);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif


    while (scanf("%d %lf %lf", &g_num, &g_l, &g_w)!=EOF)
    {
        g_w2 = (g_w/2.0f)*(g_w/2.0f);
        int valid_idx = 0;
        for (int i = 0; i < g_num; i++)
        {
            double x,r;
            scanf("%lf %lf", &x, &r);
            // 过滤洒水半径不足宽的情况。
            if (r >= g_w/2)
            {
                // 将洒水半径换算成一个线段
                double l = get_distance(r);
                g_node[valid_idx].x1 = x-l;
                g_node[valid_idx].x2 = x+l;
                valid_idx++;
            }
        }
        g_num = valid_idx;

        // 从线段左边的端点，从左往右排序
        qsort(g_node, g_num, sizeof(Node), comp);

        if (proc())
        {
            printf("%d\n", g_selected_num);
        }
        else
            printf("-1\n");

    }

    return 0;
}

bool proc()
{
    g_selected_num = 0;
    double rect_left_x = 0;
    double right_x = -1;

    int i = 0;
    while (i < g_num)
    {
        // 剪枝
        if (g_node[i].x1 > rect_left_x || g_node[i].x1 > g_l)
             return false;

        while (i < g_num && 
            g_node[i].x1 <= rect_left_x)
        {
            if (g_node[i].x2 > right_x)
            {
                right_x = g_node[i].x2;
            }
            i++;
            // 如果完全覆盖，返回true
             if (right_x+EPS >= g_l)
             {
                 g_selected_num++;
                 return true;
             }
        }

        g_selected_num++;
        rect_left_x = right_x;
    }

    // 最后没有覆盖，返回false。这也是我一直RA的地方。
    return false;
}