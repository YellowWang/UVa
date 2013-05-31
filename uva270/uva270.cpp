// uva270 暴力
// 应该有贪心的方法

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

#define len 701
struct Point
{
    int x,y;
};
Point g_points[len];
int g_num;
int proc();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    char in_str[64];
    gets(in_str);
    int cases = atoi(in_str);
    gets(in_str);
    while (cases--)
    {
        int idx = 0;
        while (gets(in_str) && in_str[0] != 0)
        {
            char * tok = strtok(in_str, " ");
            g_points[idx].x = atoi(tok);
            tok = strtok(NULL, " ");
            g_points[idx].y = atoi(tok);
            idx++;
        }
        g_num = idx;
        printf("%d\n", proc());
        if (cases != 0)
            printf("\n");
     }

    return 0;
}

int get_in_line(int point1, int point2, int startidx)
{
    // (x1-x2)*(y2-y3)=(y1-y2)*(x2-x3)
    int sumx = g_points[point1].x - g_points[point2].x;
    int sumy = g_points[point1].y - g_points[point2].y;

    // 最少2个点共线
    int in_line_num = 2;
    for (int i = startidx; i < g_num; i++)
    {
        if (sumx*(g_points[point2].y - g_points[i].y) == 
            sumy*(g_points[point2].x - g_points[i].x))
            in_line_num++;
    }
    return in_line_num;
}

int proc()
{
    int max_num = 0;
    // 枚举所有两个点 
    for (int i = 0; i < g_num; i++)
    {
        for (int k = i+1; k < g_num; k++)
        {
            int temp_num = get_in_line(i,k,k+1);
            if (temp_num > max_num)
                max_num = temp_num;
        }
    }
    return max_num;
}