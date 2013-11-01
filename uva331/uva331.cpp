// uva331 回溯
// 建立模型后，题就很简单了

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
int num;
int g_d[len];
void search(int layers, int n);
int g_sum;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int cases = 1;
    while (scanf("%d",&num) && num)
    {
        for (int i = 0; i < num; i++)
        {
            scanf("%d", &g_d[i]);
        }

        g_sum = 0;

        search(0, num);
        printf("There are %d swap maps for input data set %d.\n", g_sum, cases++);
    }

    return 0;
}

void search(int layers, int n)
{
    bool sorted = true;
    for (int i = 0; i < n-1; i++)
    {
        if (g_d[i] > g_d[i+1])
        {
            sorted = false;
            break;
        }
    }
    if (sorted && layers > 0)
    {
        g_sum++;
        return;
    }

    for (int i = 0; i < n-1; i++)
    {
        if (g_d[i] > g_d[i+1])
        {
            int t = g_d[i];
            g_d[i] = g_d[i+1];
            g_d[i+1] = t;

            search(layers+1, n);

            t = g_d[i];
            g_d[i] = g_d[i+1];
            g_d[i+1] = t;
        }
    }

}