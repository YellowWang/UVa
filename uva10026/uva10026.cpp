// uva10026 贪心简单题
//

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

#define len 128
#define node_len 1001
#define EPS 0.000001f
struct Node
{
    int x,y;
    int idx;
    float ratio;
};
Node g_d[node_len];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    char str[len];
    gets(str);
    int cases = atoi(str);

    while (cases--)
    {
        gets(str); // 空行
        gets(str);
        int num = atoi(str);

        for (int i = 0; i < num; i++)
        {
            gets(str);
            char * tok = strtok(str, " ");
            g_d[i].x = atoi(tok);
            tok = strtok(NULL, " ");
            g_d[i].y = atoi(tok);
            g_d[i].idx = i+1;
            g_d[i].ratio = (float)g_d[i].y / (float)g_d[i].x;
        }

        // 根据ratio从大到小稳定排序，这里用冒泡
        for (int i = 0; i < num-1; i++)
        {
            for (int k = 0; k < num-1-i; k++)
            {
                if (g_d[k].ratio + EPS < g_d[k+1].ratio)
                {
                    Node t = g_d[k];
                    g_d[k] = g_d[k+1];
                    g_d[k+1] = t;
                }
            }
        }

        // 输出
        printf("%d", g_d[0].idx);
        for (int i = 1; i < num; i++)
        {
            printf(" %d", g_d[i].idx);
        }
        printf("\n");

        if (cases != 0)
            printf("\n");
    }

    return 0;
}