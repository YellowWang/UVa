// uva10020 贪心
// 线段最小覆盖问题

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

#define len 100000
struct Point
{
    int x1, x2;
};
Point g_points[len];
int g_num;
bool proc(int dest_x1, int dext_x2, deque<int>& q);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    char str[64];
    gets(str);
    int cases = atoi(str);

    while (cases--)
    {
        gets(str);
        gets(str);
        int M = atoi(str);

        int i = 0;
        while (gets(str))
        {
            char * tok = strtok(str, " ");
            g_points[i].x1 = atoi(tok);
            tok = strtok(NULL, " ");
            g_points[i].x2 = atoi(tok);
            if (g_points[i].x1 == 0 && g_points[i].x2 == 0)
                break;
            i++;
        }
        g_num = i;

        deque<int> q;
        if (proc(0, M, q))
        {
            printf("%d\n", q.size());
            for (int i = 0; i < q.size(); i++)
            {
                printf("%d %d\n", g_points[q[i]].x1, g_points[q[i]].x2);
            }
        }
        else
            printf("0\n");

        if (cases != 0)
            printf("\n");
    }

    return 0;
}

int comp(const void* a, const void* b)
{
    return ((Point*)a)->x1 - ((Point*)b)->x1;
}

bool proc(int dest_x1, int dext_x2, deque<int>& q)
{
    // 按照左端点坐标由小到大排序
    qsort(g_points, g_num, sizeof(Point), comp);

    // 逐个遍历
    int x1 = dest_x1; // 目的左端点
    int x2 = -1; // 最右点
    int i = 0;
    while (i < g_num)
    {
        int selected_idx = -1;
        // 无法覆盖
        if (g_points[i].x1 > x1 || (g_points[i].x1 > dext_x2))
            return false;
        // 左端点大于0并且在前一段最右点的左边。找到最右点。
        while (g_points[i].x1 <= x1)
        {
            if (g_points[i].x2 > x2)
            {
                selected_idx = i;
                x2 = g_points[i].x2;
                // 是否完全覆盖
                if (x2 >= dext_x2)
                {
                    q.push_back(selected_idx);
                    return true;
                }
            }
            i++;
        }
        if (selected_idx == -1)
            return false;
        x1 = x2;
        q.push_back(selected_idx);
    }
    return fales;
}